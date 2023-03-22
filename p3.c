#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    int numbers[1000];
    int n = atoi(argv[2]); 
    int x = atoi(argv[1]); 
    int numbers_per_process = 1000 / n;
    int remaining_numbers = 1000 % n;
    int start;
    int end;
    pid_t pid;


    int i = 0;
    char buffer[256];
    while (fgets(buffer, 256, stdin) != NULL && i < 1000) {
        numbers[i++] = atoi(buffer);
    }

    for (int p = 0; p < n; p++) {
        pid = fork();
        if (pid == -1) {
            printf("fork error\n");
            exit(1);
        } else if (pid == 0) {
            start = p * numbers_per_process;
                if (p == n-1){
                    end = 999;
                }
                else{
                    end = start + numbers_per_process - 1 + remaining_numbers;
                }
            for (int j = start; j <= end; j++) {
                if (numbers[j] == x) {
                    printf("number %d at index %d\n", x, j);
                    exit(0);
                }
            }
            exit(1);
        }
    }

    int status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status)) {
            for (int p = 0; p < n; p++) {
                if (p != pid) {
                    kill(pid, SIGKILL);
                }
            }
            exit(0);
        }
    }
    printf("number not found\n");
    return 0;
}
