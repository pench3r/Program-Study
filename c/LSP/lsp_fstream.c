#include <stdio.h>
#include <string.h>

typedef struct my_msg_ {
	unsigned int len;
	char sender[10];
	char body[100]; 
} MY_MSG;

int main(int argc, char *argv[]) {
	// init msg that is want to send
	MY_MSG f_msg;
	char sender[] = "LSP_PRO";
	char content[] = "hello, this is a message!";
	memset(f_msg.body, 0, 10);
	memset(f_msg.sender, 0, 100);
	f_msg.len = strlen(sender) + strlen(content);
	memcpy(f_msg.body, content, strlen(content));
	memcpy(f_msg.sender, sender, strlen(sender));
	// using fwrite write msg to the file
	FILE *out_file;
	out_file = fopen("data", "w+");
	int re_num = fwrite(&f_msg, sizeof(MY_MSG), 1, out_file);
	fclose(out_file);
	// using fread recv msg from that file
	MY_MSG r_msg;
	memset(&r_msg, 0, sizeof(MY_MSG));
	FILE *in_file;
	in_file = fopen("data", "r");
	re_num = fread(&r_msg, sizeof(MY_MSG), 1, in_file);

	// print recv msg
	printf("recv len: %d\n", r_msg.len);
	printf("recv sender: %s\n", r_msg.sender);
	printf("recv content: %s\n", r_msg.body);
	return 0;
}
