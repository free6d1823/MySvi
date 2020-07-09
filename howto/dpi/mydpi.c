#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int mychar(int c)
{
	static int fd = -1;
	struct termios tty;
	char ch;
	int ret;

	if (fd == -1) {
		fd = open("/dev/tty", O_RDWR);
		tcgetattr(fd, &tty);
		tty.c_lflag &= ~(ECHO | ICANON);
		tty.c_cc[VMIN] = 0;
		tty.c_cc[VTIME] = 0;
		tcsetattr(fd, TCSAFLUSH, &tty);
	}

	if (c) {
		ch = c;
		write(fd, &ch, 1);
		return 0;
	}

	ret = read(fd, &ch, 1);
	if (ret == 0)
		return 0;

	return ch;
}


/*   udp server    */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER_LEN 1024

static int server_fd = -1;
static char rbuf[BUFFER_LEN];
static int rlen = -1;
static struct sockaddr src_addr;
static socklen_t addrlen;
static char sbuf[BUFFER_LEN];
static int pos;

int do_jtag()
{
	int ret;
	struct sockaddr_in ser_addr;

	if (server_fd < 0) {
		/* create udp server */
		server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
		memset(&ser_addr, 0, sizeof(ser_addr));
		ser_addr.sin_family = AF_INET;
		ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		ser_addr.sin_port = htons(10086);
		ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
		if (ret < 0) {
			printf("socket bind fail!\n");
			close(server_fd);
			server_fd = -1;
			return -1;
		}
	}

	if (rlen <= 0) {
		/* receive one packet */
		addrlen = sizeof(src_addr);
		rlen = recvfrom(server_fd, rbuf, sizeof(rbuf), MSG_DONTWAIT, &src_addr, &addrlen);

		if (rlen <= 0) return -1;

		pos = 0;
	}

	return rbuf[pos];
}

void do_jtag_tdo(int tdo)
{
	if (rlen <= 0) return;

	sbuf[pos++] = tdo;

	/* got full data */
	if (rlen == pos) {
		sendto(server_fd, sbuf, rlen, 0, &src_addr, addrlen);
		/* ready to recv the next packet */
		rlen = -1;
	}
}

#if 0
int main(int argc, char**argv)
{
	int i;

	while (rlen <= 0) {
		do_jtag();
	}

	while (rlen > 0) {
		do_jtag_tdo(pos);
	}

	while (rlen <= 0) {
		do_jtag();
	}

	while (rlen > 0) {
		do_jtag_tdo(pos);
	}

	return 0;
}
#endif
