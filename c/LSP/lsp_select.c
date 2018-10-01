#include <sys/select.h> /* select */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> /* STDIN_FILENO */
#include <string.h> /* strlen */

int main(int argc, char *argv[]) {
	fd_set read_fd_set;
	FD_ZERO(&read_fd_set);
	FD_SET(STDIN_FILENO, &read_fd_set);

	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	// int stdin_fd = fcntl(STDIN_FILENO, F_DUPFD);
	int re_num = select(STDIN_FILENO + 1, &read_fd_set, NULL, NULL, &timeout);
	if (re_num != -1 && re_num != 0) {
		// read avaiable
		if (FD_ISSET(STDIN_FILENO, &read_fd_set)) {
			char recv_data[10];
			memset(recv_data, 0, 10);
			re_num = read(STDIN_FILENO, recv_data, 10);
			if (re_num == -1) {
				printf("read error.\n");
				return -1;
			}
			printf("data is: %s", recv_data);
		}
	}
	
	return 0;
}
