#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"


//This is where you'll need to implement the user-level functions
 


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
    return -1;
}

int thread_create(void (*start_routine)(void *), void *arg) {
	return -1;
}

