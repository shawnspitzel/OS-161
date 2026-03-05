#include <thread.h>
#include <stdio.h>
#include <lib.h>
void _exit(int exitCode){
    thread_exit(exitCode); // Why do we even need to modify this?
}

int printint(int c){
    kprintf("%d", c);
    return c % 5 == 0;
}