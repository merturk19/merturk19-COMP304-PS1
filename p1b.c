#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid = fork();
	if (pid > 0){
		sleep(5);
	}
	else{
		exit(0);
	}
	return 0;
}
