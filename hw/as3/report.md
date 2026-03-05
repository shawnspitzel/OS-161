## Part A:
### Files Changed:
    - Altered kern/thread/thread.c, and added new as3.c file added for implementation of our new function. 
    - I altered thread.c by passing int exitCode as a parameter to thread_exit(), and then printing it. You can also simply print exitCode in the caller function, but for full robustness in case our thread_exit() function fails, it's better practice to put it inside the function.
    - List of files in which I had to pass in an exit code to thread_exit():
        - kern/thread/thread.c:420 <- pass in 0
        - kern/thread/thread.c:784 <- pass in 0
        - kern/test/synchtest.c:493 <- pass in 0
        - kern/syscall/proc_syscall_strcopy.c:176 <- pass in 0
        - kern/syscall/proc_syscall_strcopy.c:183 <- pass in 0
        - kern/syscall/proc_syscall_newexec.c:198 <- pass in 0
        - kern/syscall/proc_syscall_newexec.c:205 <- pass in 0
        - kern/syscall/proc_syscall.c:196 <- pass in exitcode
        - kern/main/menu.c:379 <- pass in 0
        - kern/arch/mips/locore/trap.c:141 <- pass in 0
### Source Code:
```C
// as3.c

#include <thread.h>`
#include <stdio.h>

    void _exit(int exitCode){
        thread_exit(exitCode);
    }
```
```C
// thread.c

void thread_exit(void)
{
	struct thread *cur;

	cur = curthread;

	/*
	 * Detach from our process. You might need to move this action
	 * around, depending on how your wait/exit works.
	 */
	proc_remthread(cur);

	/* Make sure we *are* detached (move this only if you're sure!) */
	KASSERT(cur->t_proc == NULL);

	/* Check the stack guard band. */
	thread_checkstack(cur);

	// Decrement the thread count and notify anyone interested.
	if (thread_count) {
		spinlock_acquire(&thread_count_lock);
		--thread_count;
		wchan_wakeall(thread_count_wchan, &thread_count_lock);
		spinlock_release(&thread_count_lock);
	}

	/* Interrupts off on this processor */
	splhigh();
	thread_switch(S_ZOMBIE, NULL, NULL);
	printf("%d", exitCode); // print out our exit code
	panic("braaaaaaaiiiiiiiiiiinssssss\n");
}
``` 
## Part B:
### Files Changed:
    - None. I simply imported #lib.h, used the kprintf function, and printed it out within as3.c.
### Source Code:
```C
// as3.c
#include <stdio.h>
#include <lib.h>

int printint(int c){
    kprintf("%d", c);
    return c % 5 == 0;
}
```
