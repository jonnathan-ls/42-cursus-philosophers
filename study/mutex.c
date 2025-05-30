
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include	<unistd.h>

int x = 1;

void *routine(void *arg)
{
	printf("current pid: %d\n", getpid());
	printf("Thread R1 is running\n");
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
		pthread_mutex_lock(mutex); // Lock the mutex before modifying x
		x++; // Increment x in a loop to increase
		pthread_mutex_unlock(mutex); // Unlock the mutex after modifying x
	}
	printf("Thread R1 is done\n");
	return NULL;
}

int main(void)
{
	pthread_t	thread_list[5];

	pthread_mutex_t mutex;
	
	if (pthread_mutex_init(&mutex, NULL) != 0) {
		perror("Failed to initialize mutex");
		return EXIT_FAILURE;
	}
	for	(int i = 0; i < 5; i++) {
		if (pthread_create(&thread_list[i], NULL, &routine, (void *)&mutex) != 0) {
			perror("Failed to create thread");
			pthread_mutex_destroy(&mutex);
			return EXIT_FAILURE;
		}
		printf("Thread %d created\n", i + 1);
	}
	for	(int i = 0; i < 5; i++) {
		if (pthread_join(thread_list[i], NULL) != 0) {
			perror("Failed to join thread");
			pthread_mutex_destroy(&mutex);
			return EXIT_FAILURE;
		}
		printf("Thread %d joined\n", i + 1);
	}
	pthread_mutex_destroy(&mutex);
	printf("Final value of x = %d\n", x);
	return EXIT_SUCCESS;
}