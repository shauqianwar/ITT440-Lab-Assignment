#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig)
{
	exit(1);
}

int main()
{
	void sigint_handler(int sig);
	
	if(signal(SIGINT, sigint_handler)==SIG_ERR){
		perror("signal");
		exit(1);
	}
	
	int pipefds[2];
	int buffer;
	int num,flag;
	
	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	
	if(pid == 0){
		printf("Enter a number: ");
		scanf("%d", &num);
		close(pipefds[0]);
		write(pipefds[1], &num, 5);
		exit(EXIT_SUCCESS);
	}
	
	if(pid > 0){
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0], &buffer, 5);
		close(pipefds[0]);
		
		for(int i=2; i<=buffer/2; i++){
			if(buffer % i == 0){
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			printf("%d is a prime number.\n", buffer);
		else 
			printf("%d is not a prime number.\n", buffer);
	}
	return EXIT_SUCCESS;
}