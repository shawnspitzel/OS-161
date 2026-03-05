#include <thread.h>
#include <stdio.h>

void _exit(int exitCode){
    thread_exit(exitCode); // Why do we even need to modify this?
}