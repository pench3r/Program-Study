#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"



int create_thread_pool(thread_pool_t **tpt, int pool_size) {
	(*tpt)->pool_size = pool_size;
	(*tpt)->thread_list = (pthread_t *)malloc(pool_size * sizeof(pthread_t));
	(*tpt)->task_list_head = NULL;
	pthread_mutex_init(&((*tpt)->task_list_clock), NULL);
	pthread_cond_init(&((*tpt)->task_list_update), NULL);
	for (int i=0; i < pool_size; ++i) { 
		if (pthread_create(&((*tpt)->thread_list[i]), NULL, (void *)task_worker, (void *)(*tpt)) != 0)	{
			printf("pthread error\n");
		}
	}
}


int add_task_to_thread_pool(thread_pool_t *tpt, void *(*func)(void *), void *args) {
	task_t *new_task = (task_t *)malloc(sizeof(task_t));
	task_t *last_task;
	new_task->func = func;
	new_task->args = args;
	new_task->next = NULL;
	pthread_mutex_lock(&(tpt->task_list_clock));
	if (!(tpt->task_list_head)) {
		tpt->task_list_head = new_task;
	} else {
		last_task = tpt->task_list_head;
		while	(last_task->next)
			last_task = last_task->next;
		last_task->next = new_task;
	}
	pthread_cond_signal(&(tpt->task_list_update));
	pthread_mutex_unlock(&(tpt->task_list_clock));
	return 0;
}

void *task_worker(void *arg) {
	task_t *runable_task;
	thread_pool_t *tpt = (thread_pool_t *)arg;
	while(1) {
		pthread_mutex_lock(&(tpt->task_list_clock));
		if (!(tpt->task_list_head)) {
			pthread_cond_wait(&(tpt->task_list_update), &(tpt->task_list_clock));
		}
		runable_task = tpt->task_list_head;
		tpt->task_list_head = runable_task->next;
		pthread_mutex_unlock(&(tpt->task_list_clock));
		runable_task->func(runable_task->args);
		free(runable_task);
	}	
	return NULL;
}


// void* fun(void* args)
// {
//    int thread = (int)args;
//    printf("running the thread of %d\n",thread);
// 	 return NULL;
// }
// 
// int main(int argc, char* args[])
// {
// 	thread_pool_t *tpt = (thread_pool_t *)malloc(sizeof(thread_pool_t));
// 	create_thread_pool(&tpt, 5); 
//   for(int i = 0; i < 100; i++){
//   	add_task_to_thread_pool(tpt, fun,(void*)i);
//   }
// 	return 0;
// }
