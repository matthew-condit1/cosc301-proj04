#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"


//This is where you'll need to implement the user-level functions

#define NUMSTACK 64
 
typedef struct	{
	void * stack;
	int pid;
} processinfo

int stackarr[NUMSTACK];
int stackcount = 0;

void lock_init(lock_t *lock) {
	lock->locked = 1; //1 == locked 0 is unlocked
}

void lock_acquire(lock_t *lock) {
	while(xchg(&lk->locked, 1) != 0);
}

void lock_release(lock_t *lock) {
	lock->locked = 0; //unlocked... have to use xchg here??
}

int thread_join(int pid) {
	int thread_pid = join(pid);
		if(thread_pid < NUMSTACK && thread_pid > 0)
		{
			free(stackarr[thread_pid - 1].stack);
		
		}
	
	return thread_pid;
}

int thread_create(void (*start_routine)(void *), void *arg) {
	void * stack = malloc(PGSIZE * 2);
	if((uint)stack % PGSIZE)
	{
		stack += PGSIZE - ((uint)stack % PGSIZE);
	}
	int thread_pid = clone(start_routine, arg, stack);
	if(thread_pid = -1)
	{
		return -1:
	}
	
	else
	{
		stackarr[stackcount].stack = stack;
		stackarr[stackcount].pid = thread_pid;
		stackcount++;
	}
	return thread_pid;
	
}

