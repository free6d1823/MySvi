#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <svdpi.h>

static int fd = -1;

int mychar(int c)
{
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

static int server_fd = -1;
static int rbuf[1024];
static int rlen = -1;
static struct sockaddr src_addr;
static socklen_t addrlen;
static int sbuf[1024];

#if 0
int do_jtag(int tdo)
{
	int ret;
	struct sockaddr_in ser_addr;

	if (server_fd < 0) {
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

	if (rlen < 0) {
		addrlen = sizeof(src_addr);
		rlen = recvfrom(server_fd, rbuf, sizeof(rbuf), MSG_DONTWAIT, &src_addr, &addrlen);
	}


}
#else
int do_jtag(int tdo)
{
	static unsigned int idcode;
	static int cur;
	static const char data[] = {2, 2, 2, 2, 2, 0, /* Run-Test/ Idle */
		2, 0, 0, /* Shift-DR */
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, /* Exit1-DR */
		};

	if (tdo == -1)
		return data[cur++ % sizeof(data)];

	idcode = (idcode >> 1) | (tdo << 31);
	if (cur % sizeof(data) == 0 && idcode)
		printf("idcode = 0x%x\n", idcode);

	return 0;
}
#endif