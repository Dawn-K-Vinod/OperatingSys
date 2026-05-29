#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror ("Fork failed!");
        return 1;
    }
    else if (pid == 0) {
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n\n", getppid());
    }
    else {
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n\n", pid);
    }
    sleep(10);
    return 0;
}
