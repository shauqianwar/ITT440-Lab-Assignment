#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	char name[20];
	for(int i=1; i<5; i++){
		pid_t pid = fork();
		
		if(pid == 0){
			printf("Enter name: ");
			scanf("%s", name);
			
			printf("Your name is %s\n", name);
		}
		else{
			//printf("Parent process => PID=%d\n", getpid());
			//printf("Waiting for child processes to finish...\n");
			wait(NULL);
			printf("Job is done\n");
			exit(0);
		}
	}
	return EXIT_SUCCESS;
}