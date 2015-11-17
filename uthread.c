#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"
#include "param.h"


//This is where you'll need to implement the user-level functions

#define NUMSTACK 64
 

int stackarr[NUMSTACK];
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
		if(thread_pid < NUMSTACK && thread_pid > 0)
		{
			free((void *) stackarr[thread_pid - 1]);
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
	if(thread_pid < 0 || thread_pid > NUMSTACK)
	{
		return -1;
	}
	stackarr[thread_pid-1] = (uint) stack;
	return thread_pid;
	
}

