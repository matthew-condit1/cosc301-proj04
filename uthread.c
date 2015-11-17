#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"
#include "param.h"


//This is where you'll need to implement the user-level functions

#define NUMSTACK 64

typedef struct __info {
	void* stack;
	int pid;
} info;

info stackarr[NUMSTACK];
int stackcount = 0;

void lock_init(lock_t *lock) {
	lock->locked = 0; //0 is locked; 1 is unlocked
}

void lock_acquire(lock_t *lock) {
	while(xchg(&lock->locked, 1) != 0); {}
}

void lock_release(lock_t *lock) {
	xchg(&lock->locked, 0);
}

int thread_join(int pid) {
	int thread_pid = join(pid);
	int i;
	for (i=0; i<stackcount;i++) {
		if(stackarr[i].pid == thread_pid)
		{
			free(stackarr[i].stack);
		}
	}
	
	return thread_pid;
}

int thread_create(void (*start_routine)(void *), void *arg) {
	void * new_stack = malloc(2*PGSIZE);
	if((uint)new_stack % PGSIZE)
	{
		new_stack = new_stack + (PGSIZE - ((uint)new_stack % PGSIZE));
	}
	info * new_info = &stackarr[stackcount];
	new_info->stack = new_stack;
	int thread_pid = clone(start_routine, arg, new_stack);
	new_info->pid = thread_pid;
	if(stackcount<NUMSTACK)
	{
		stackcount++;
	}
	return thread_pid;
	
}

