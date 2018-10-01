#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	struct pollfd stdin_pollfd;
	stdin_pollfd.fd = STDIN_FILENO;
	stdin_pollfd.events = POLLRDNORM;
	char recv_data[5] = {0};
	memset(recv_data, 0, 5);
	while (1) {
		switch(poll(&stdin_pollfd, 1, 5000)) {
			case 0:
				printf("time out.\n");
				break;
			case -1:
				printf("poll failed.\n");
				break;
			default:
				printf("fd event value is 0x%x.\n", stdin_pollfd.revents);
				read(STDIN_FILENO, recv_data, 5);
				printf("data: %s\n", recv_data);
				break;
		}
	}
	return 0;
}
