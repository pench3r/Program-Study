#include <pthread.h>


typedef struct task_t_{
	void *(*func)(void *);
	void *args;
	struct task_t_ *next;
}task_t;

typedef struct thread_pool_t_{
	int pool_size;
	pthread_t *thread_list;	
	task_t *task_list_head;
	pthread_mutex_t task_list_clock;
	pthread_cond_t task_list_update;
}thread_pool_t;

// create thread pool
int create_thread_pool(thread_pool_t **tpt, int pool_size);

// destory thread pool
int destory_thread_pool(thread_pool_t *tpt);

// add task 
int add_task_to_thread_pool(thread_pool_t *tpt, void *(*task)(void *), void *arg);

// task routine
void *task_worker(void *tpt);
