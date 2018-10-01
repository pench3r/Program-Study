#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> /* create, write, read */
#include <string.h> /* strlen */

int main(int argc, char *argv[]) {
	int fd;
	// open target file, create if that file not exist
	fd = open("lsp_file.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1) {
		printf("Create File Failed!\n");
		return -1;
	}
	// fd = open("lsp_file.txt", O_RDWR);

	// write some data to fd
	char writed_data[] = "hello world\n";
	int res = write(fd, writed_data, strlen(writed_data));
	if ( res == -1) {
		printf("Write File Failed.\n");
		return -1;
	}
	printf("first line size: %lu\n", strlen(writed_data));
	
	// write second line
	char writed_data1[] = "this is second line\n";
	res = write(fd, writed_data1, strlen(writed_data1));
	if ( res == -1) {
		printf("Write File Failed.\n");
		return -1;
	}
	// reposition offset of fd
	lseek(fd, SEEK_SET, 0);
	// attempt to read data
	int recv_size = strlen(writed_data) + strlen(writed_data1);
	char readed_data[recv_size];
	memset(readed_data, 0, recv_size);
	res = read(fd, readed_data, recv_size);
	if ( res == -1 ) {
		printf("Read File Failed.\n");
		return -1;
	}
	printf("total size: %d, read data: %s.", recv_size, readed_data);
	
	return 0;
}

