

#include	<stdio.h>
#include	<unistd.h>
#include	<sys/wait.h>

int main(void)
{
	int x	= 1;
	int pid = fork();
	printf("current process id: %d\n", getpid());
	if (pid < 0) {
		perror("Failed to fork");
		return 1;
	} else if (pid == 0) {
		x++;
		printf("Child process is running\n");
		sleep(2);
		printf("Child process is done\n");
	} else {
		printf("Parent process is running\n");
		wait(NULL); // Wait for the child process to finish
		printf("Parent process is done\n");
	}
	printf("x = %d\n", x);
	return 0;
}