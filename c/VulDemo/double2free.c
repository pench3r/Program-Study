#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void (*operation)();

void menu();
void create_exp();
void delete_exp();
void edit_exp();
void show_exp();
void exit_exp();
int recv_user_choice();

// global variable
int total_num = 0;
operation oper_array[6] = {
		menu,
		create_exp,
		delete_exp,
		edit_exp,
		show_exp,
		exit_exp
	};

void * exp_repo[10];
int exp_pre_len[5];
// void * exp_repo;

void create_exp() {
	int exp_len;
	int exp_index;
	char *exp_content;
	if (total_num < 5) {
		puts("input lenght: ");	
		exp_len = recv_user_choice();	
		puts("input exp index: ");
		exp_index = recv_user_choice();
		if (exp_index <= 4) {
			exp_content = malloc(exp_len);
			puts("Input content: ");
			read(STDIN_FILENO, exp_content, (unsigned int)exp_len);	
			*(exp_repo + exp_index*2) = (void *)exp_content;
			*(exp_repo + exp_index*2 + 1) = (void *)1;
			*(exp_pre_len + exp_index) = exp_len;
			total_num++;
		}
	}
}

void delete_exp() {
	puts("Chose one to delete: ");
	int exp_index = recv_user_choice();
	if (exp_index < 5) {
		free(*(exp_repo + exp_index*2));
		*(exp_repo + exp_index*2 + 1) = (void *)0;
		total_num--;
		puts("Delete Success!\n");
	}
}

void edit_exp() {
	int exp_index;
	puts("chose one to edit: ");
	exp_index = recv_user_choice();
	if (exp_index <=4) {
		ssize_t flag = (ssize_t)(*(exp_repo + exp_index*2 + 1));
		if (flag == 1) {
			puts("Input Content: ");
			read(STDIN_FILENO, *(exp_repo + exp_index*2), *(exp_pre_len + exp_index));
			puts("Edit success!\n");
		}
	}
}

void show_exp() {
	puts("NO NO NO ~~~\n");
}

void exit_exp() {
	puts("Bye Bye!!!\n");
	exit(0);
}

void menu()
{
	puts("******************************");
	puts("Welcome to my black weapon storage!");
	puts("Now you can use it to do some evil things");
	puts("1. create exploit");
	puts("2. delete exploit");
	puts("3. edit exploit");
	puts("4. show exploit");
	puts("5. exit");
	puts("******************************");
	printf("The total exploit number is %d.\n", total_num);
	write(1, "$ ", 2uLL);
	return;
}

void func_init() {
	char *name;
	setvbuf(stdin, 0, _IONBF, 2);
	setvbuf(stderr, 0, _IONBF, 2);
	setvbuf(stdout, 0, _IONBF, 2);
	puts("Input your name: ");
	write(1, "$ ", 2);
	name = malloc(sizeof(int)*8);
	read(STDIN_FILENO, name, 32);
	write(STDOUT_FILENO, "Hello ", 6);
	puts(name);	
	return;
}

int recv_user_choice() {
	char buf[12];
	read(STDIN_FILENO, buf, 12);
	return atoi(buf);
}

int main(int argc, char *argv[]) {
	int user_choice;
	func_init();
	while (1) {
		menu();
		user_choice = recv_user_choice();
		if (user_choice > 5) {
			puts("bad choice");
			continue;
		}
		oper_array[user_choice]();
	}
	return 0;
}
