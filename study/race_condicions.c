
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include	<unistd.h>

int x = 1;

void *routine()
{
	printf("current pid: %d\n", getpid());
	printf("Thread R1 is running\n");
	x++;
	sleep(1);
	printf("x = %d\n", x);
	printf("Thread R1 is done\n");
	return NULL;
}

void *routine2()
{
	printf("current pid: %d\n", getpid());
	printf("Thread R2 is running\n");
	sleep(1);
	printf("x = %d\n", x);
	printf("Thread R2 is done\n");
	return NULL;
}

int main(void)
{
	pthread_t	thread_1, thread_2;

	if	(pthread_create(&thread_1, NULL, &routine, NULL) != 0) {
		perror("Failed to create thread 1");
		return EXIT_FAILURE;
	}
	if (pthread_create(&thread_2, NULL, &routine2, NULL) != 0) {
		perror("Failed to create thread 2");
		pthread_cancel(thread_1);
		return EXIT_FAILURE;
	}
	if (pthread_join(thread_1, NULL) != 0) {
		perror("Failed to join thread 1");
		pthread_cancel(thread_2);
		return EXIT_FAILURE;
	}
	if (pthread_join(thread_2, NULL) != 0) {
		perror("Failed to join thread 2");
		pthread_cancel(thread_1);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}