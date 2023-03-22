#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    char *command = argv[2];
    char *command_detail = argv[3];
    int fd[n][2];
    struct timeval start, finish;
    pid_t pid;
    pid_t gc_pid;
    double time_elapsed;
    int count = 0;
    double time_table[n];
    double sum;
    double max_time;
    double min_time;
   printf("command: %s %s\n", command, command_detail); 


    for (int i=0; i<n; i++){
        if(pipe(fd[i])==-1){
            perror("Pipe error!");
            exit(1);
        }
    }

    for (int i=0; i<n; i++){
    	pid = fork();
        if (pid==0){
            close(fd[i][0]);
            gettimeofday(&start, NULL);
            gc_pid = fork();
            if (gc_pid == 0){
                freopen("/dev/null", "w", stdout);
                execlp(command,command, command_detail,NULL);
                exit(0);
            }
            else{
		wait(NULL);
                gettimeofday(&finish, NULL);
                time_elapsed = ((finish.tv_sec - start.tv_sec) * 1000.0) + ((finish.tv_usec - start.tv_usec) / 1000.0);
                write(fd[i][1], &time_elapsed, sizeof(time_elapsed));
                exit(0);
            }   
        }
        else{
            close(fd[i][1]);
        }
    }

    for (int i = 0; i<n; i++){
        read(fd[i][0], &time_table[i], sizeof(time_table[i]));
	close(fd[i][0]);
    }

    max_time = 0.0;
    min_time = 999999999.0;
    for(int i=0; i<n; i++){
        sum += time_table[i];
        if (max_time <= time_table[i]){
            max_time = time_table[i];
            }
        if (min_time >= time_table[i]){
            min_time = time_table[i];
            }
    }



    double average = sum/n;
    for (int i=0; i<n; i++){
            printf("Child %d Executed in %.2f millis\n", i+1, time_table[i]);
        }
    
    printf("Max: %.2f millis\n", max_time);
    printf("Min: %.2f millis\n", min_time);
    printf("Average: %.2f millis\n", average);

    exit(0);
}
