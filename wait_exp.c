#include <stdio.h>
#include <unistd.h> /*POSIX standard header file in C that provides access to operating system services*/
#include <sys/types.h>  /*POSIX / UNIX header file that defines data types used in system calls and low-level OS programming.*/
#include <sys/wait.h>

int main(void) {
    pid_t pid; //declares a variable pid of type pid_t, which is used to store a process ID.
    pid = fork();   // create a new process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
    	printf("24SJPCCSL407 ");
    } 
    else {
    	wait(NULL);
    	printf("Operating Systems Lab\n");
    }
    return 0;
}
