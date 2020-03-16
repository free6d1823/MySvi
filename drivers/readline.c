/*
 * cmdline-editing related codes from vivi.
 * Author: Janghoon Lyu <nandy@mizi.com>
 */
#include <target/compiler.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <target/readline.h>
#include <target/uart.h>


#define putnstr(str, n)		printf("%.*s", (int)n, str)
#define cbeep()			putch('\a')

#define CTL_CH(c)		((c) - 'a' + 1)
#define CTL_BACKSPACE		('\b')
#define DEL			((char)255)
#define DEL7			((char)127)
#define CREAD_HIST_CHAR		('!')

static char cbuf[READLINE_BUFFER_SIZE + 1];	/* console I/O buffer	*/
static unsigned long cur_num;
static unsigned long eol_num = 0;
static int esc_len = 0;
static char esc_save[8];
static readline_cmd_handler readline_handler = NULL;

#define HIST_MAX		20
#define HIST_SIZE		READLINE_BUFFER_SIZE

static int hist_max;
static int hist_add_idx;
static int hist_cur = -1;
static unsigned hist_num;

static char *hist_list[HIST_MAX];
static char hist_lines[HIST_MAX][HIST_SIZE + 1];	/* Save room for NULL */
#define add_idx_minus_one()	\
	((hist_add_idx == 0) ? hist_max : hist_add_idx-1)

static void hist_init(void)
{
	int i;

	hist_max = 0;
	hist_add_idx = 0;
	hist_cur = -1;
	hist_num = 0;

	for (i = 0; i < HIST_MAX; i++) {
		hist_list[i] = hist_lines[i];
		hist_list[i][0] = '\0';
	}
}

static void cread_add_to_hist(char *line)
{
	strcpy(hist_list[hist_add_idx], line);

	if (++hist_add_idx >= HIST_MAX)
		hist_add_idx = 0;

	if (hist_add_idx > hist_max)
		hist_max = hist_add_idx;

	hist_num++;
}

static char *hist_prev(void)
{
	char *ret;
	int old_cur;

	if (hist_cur < 0)
		return NULL;

	old_cur = hist_cur;
	if (--hist_cur < 0)
		hist_cur = hist_max;

	if (hist_cur == hist_add_idx) {
		hist_cur = old_cur;
		ret = NULL;
	} else {
		ret = hist_list[hist_cur];
	}

	return ret;
}

static char *hist_next(void)
{
	char *ret;

	if (hist_cur < 0)
		return NULL;

	if (hist_cur == hist_add_idx)
		return NULL;

	if (++hist_cur > hist_max)
		hist_cur = 0;

	if (hist_cur == hist_add_idx)
		ret = "";
	else
		ret = hist_list[hist_cur];

	return ret;
}

#if 0
static void cread_print_hist_list(void)
{
	int i;
	unsigned long n;

	n = hist_num - hist_max;
	i = hist_add_idx + 1;
	while (1) {
		if (i > hist_max)
			i = 0;
		if (i == hist_add_idx)
			break;
		printf("%s\n", hist_list[i]);
		n++;
		i++;
	}
}
#endif

#define BEGINNING_OF_LINE() {				\
	while (cur_num) {			\
		putch(CTL_BACKSPACE);			\
		cur_num--;			\
	}						\
}

#define ERASE_TO_EOL() {						\
	if (cur_num < eol_num) {			\
		wlen = eol_num - cur_num;		\
		printf("%*s", (int)wlen, "");				\
		do {							\
			putch(CTL_BACKSPACE);				\
		} while (--eol_num > cur_num);	\
	}								\
}

#define REFRESH_TO_EOL() {						\
	if (cur_num < eol_num) {			\
		wlen = eol_num - cur_num;		\
		putnstr(cbuf + cur_num, wlen);	\
		cur_num = eol_num;			\
	}								\
}

static void cread_add_char(char ichar, int insert)
{
	unsigned long wlen;

	/* room ??? */
	if (insert || cur_num == eol_num) {
		if (eol_num > READLINE_BUFFER_SIZE - 1) {
			cbeep();
			return;
		}
		eol_num++;
	}

	if (insert) {
		wlen = eol_num - cur_num;
		if (wlen > 1)
			memmove(&cbuf[cur_num +1],
				&cbuf[cur_num], wlen-1);

		cbuf[cur_num] = ichar;
		putnstr(cbuf + cur_num, wlen);
		cur_num++;
		while (--wlen)
			putch(CTL_BACKSPACE);
	} else {
		/* echo the character */
		wlen = 1;
		cbuf[cur_num] = ichar;
		putnstr(cbuf + cur_num, wlen);
		cur_num++;
	}
}

static void cread_add_str(char *str, int strsize, int insert)
{
	while (strsize--) {
		cread_add_char(*str, insert);
		str++;
	}
}

static void readline_reset_buffer(void)
{
	memset(cbuf, 0, READLINE_BUFFER_SIZE);
	cur_num = 0;
	eol_num = 0;
	esc_len = 0;
}

static int readline_mode(int async)
{
	unsigned long wlen;
	char *hline;
	char ichar;
	int insert = 1;
	readline_cmd_handler handler;

	if (async == 1)
		ichar = getch();
	else {
		while (!uart_poll()); // do we have tstc()?
		ichar = getch();
	}
	if ((ichar == '\n') || (ichar == '\r')) {
		putch('\r');
		putch('\n');

		cbuf[eol_num] = '\0';	/* lose the newline */
		if (cbuf[0] && cbuf[0] != CREAD_HIST_CHAR)
			cread_add_to_hist(cbuf);
		hist_cur = hist_add_idx;

		handler = readline_handler;
		if (handler) handler(cbuf, eol_num);

		readline_reset_buffer();
		return eol_num;
	}
	/*
	 * handle standard linux xterm esc sequences for arrow key, etc.
	 */
	if (esc_len != 0) {
		enum { ESC_REJECT, ESC_SAVE, ESC_CONVERTED } act = ESC_REJECT;
			if (esc_len == 1) {
			if (ichar == '[' || ichar == 'O')
				act = ESC_SAVE;
		} else if (esc_len == 2) {
			switch (ichar) {
			case 'D':	/* <- key */
				ichar = CTL_CH('b');
				act = ESC_CONVERTED;
				break;	/* pass off to ^B handler */
			case 'C':	/* -> key */
				ichar = CTL_CH('f');
				act = ESC_CONVERTED;
				break;	/* pass off to ^F handler */
			case 'H':	/* Home key */
				ichar = CTL_CH('a');
				act = ESC_CONVERTED;
				break;	/* pass off to ^A handler */
			case 'F':	/* End key */
				ichar = CTL_CH('e');
				act = ESC_CONVERTED;
				break;	/* pass off to ^E handler */
			case 'A':	/* up arrow */
				ichar = CTL_CH('p');
				act = ESC_CONVERTED;
				break;	/* pass off to ^P handler */
			case 'B':	/* down arrow */
				ichar = CTL_CH('n');
				act = ESC_CONVERTED;
				break;	/* pass off to ^N handler */
			case '1':
			case '3':
			case '4':
			case '7':
			case '8':
				if (esc_save[1] == '[') {
					/* see if next character is ~ */
					act = ESC_SAVE;
				}
				break;
			}
		} else if (esc_len == 3) {
			if (ichar == '~') {
				switch (esc_save[2]) {
				case '3':	/* Delete key */
					ichar = CTL_CH('d');
					act = ESC_CONVERTED;
					break;	/* pass to ^D handler */
				case '1':	/* Home key */
				case '7':
					ichar = CTL_CH('a');
					act = ESC_CONVERTED;
					break;	/* pass to ^A handler */
				case '4':	/* End key */
				case '8':
					ichar = CTL_CH('e');
					act = ESC_CONVERTED;
					break;	/* pass to ^E handler */
				}
			}
		}
		switch (act) {
		case ESC_SAVE:
			esc_save[esc_len++] = ichar;
			return -EAGAIN;
		case ESC_REJECT:
			esc_save[esc_len++] = ichar;
			cread_add_str(esc_save, esc_len, insert);
			esc_len = 0;
			return -EAGAIN;
		case ESC_CONVERTED:
			esc_len = 0;
			break;
		}
	}
	switch (ichar) {
	case 0x1b:
		if (esc_len == 0) {
			esc_save[esc_len] = ichar;
			esc_len = 1;
		} else {
			puts("impossible condition #876\n");
			esc_len = 0;
		}
		break;
	case CTL_CH('a'):
		BEGINNING_OF_LINE();
		break;
	case CTL_CH('c'):	/* ^C - break */
		*cbuf = '\0';	/* discard input */

		handler = readline_handler;
		if (handler) handler(NULL, -1);

		readline_reset_buffer();
		return -EINTR;
	case CTL_CH('f'):
		if (cur_num < eol_num) {
			putch(cbuf[cur_num]);
			cur_num++;
		}
		break;
	case CTL_CH('b'):
		if (cur_num) {
			putch(CTL_BACKSPACE);
			cur_num--;
		}
		break;
	case CTL_CH('d'):
		if (cur_num < eol_num) {
			wlen = eol_num - cur_num - 1;
			if (wlen) {
				memmove(&cbuf[cur_num],
					&cbuf[cur_num +1], wlen);
				putnstr(cbuf + cur_num, wlen);
			}
			putch(' ');
			do {
				putch(CTL_BACKSPACE);
			} while (wlen--);
			eol_num--;
		}
		break;
	case CTL_CH('k'):
		ERASE_TO_EOL();
		break;
	case CTL_CH('e'):
		REFRESH_TO_EOL();
		break;
	case CTL_CH('o'):
		insert = !insert;
		break;
	case CTL_CH('x'):
	case CTL_CH('u'):
		BEGINNING_OF_LINE();
		ERASE_TO_EOL();
		break;
	case DEL:
	case DEL7:
	case 8:
		if (cur_num) {
			wlen = eol_num - cur_num;
			cur_num--;
			memmove(&cbuf[cur_num],
				&cbuf[cur_num +1], wlen);
			putch(CTL_BACKSPACE);
			putnstr(cbuf + cur_num, wlen);
			putch(' ');
			do {
				putch(CTL_BACKSPACE);
			} while (wlen--);
			eol_num--;
		}
		break;
	case CTL_CH('p'):
	case CTL_CH('n'):
		esc_len = 0;
		if (ichar == CTL_CH('p'))
			hline = hist_prev();
		else
			hline = hist_next();
		if (!hline) {
			cbeep();
			return -EAGAIN;
		}
		/* nuke the current line */
		/* first, go home */
		BEGINNING_OF_LINE();
		/* erase to end of line */
		ERASE_TO_EOL();
		/* copy new line into place and display */
		strcpy(cbuf, hline);
		eol_num = strlen(cbuf);
		REFRESH_TO_EOL();
		return -EAGAIN;
	default:
		cread_add_char(ichar, insert);
		break;
	}

	return -EAGAIN;
}

int readline_async(void)
{
	return readline_mode(1);
}

int readline_sync(void)
{
	return readline_mode(0);
}

int readline(void)
{
	int ret;

	while (1) {
		ret = readline_sync();
		if (ret != -EAGAIN)
			break;
	}
	return ret;
}

int readline_register_handler(readline_cmd_handler handler)
{
	if (readline_handler)
		return -EBUSY;
	readline_handler = handler;
	return 0;
}

int readline_init(void)
{
	readline_handler = NULL;
	readline_reset_buffer();
	hist_init();
	return 0;
}
