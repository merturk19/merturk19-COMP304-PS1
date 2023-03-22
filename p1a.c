#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int value, pid, mypid, parentpid;
	int limit = atoi(argv[1]);
	value = 0;
	if(value == 0) {
		mypid = getpid();
		printf("Main Process ID: %d, level: %d\n", mypid, value);

	}
	for (int i = 0; i<limit; i++){
		pid=fork();
		if (pid==0){
			mypid=getpid();
			parentpid=getppid();
			value++;
			printf("Process ID: %d, Parent ID: %d level: %d\n", mypid, parentpid, value);
		}
		else{
			wait(NULL);
		}
	}
}
