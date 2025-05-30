
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include	<unistd.h>

int x = 1;

void *routine(void *arg)
{
	int _arg = (int)arg;
	int *value = malloc(sizeof(int));
	if (value == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}
	*value = _arg * 2;
	printf("Routine value: %d\n", *value);
	return (void *)value;
}

int main(void)
{
	pthread_t	thread_list[5];
	int *result;
	pthread_mutex_t mutex;
	
	if (pthread_mutex_init(&mutex, NULL) != 0) {
		perror("Failed to initialize mutex");
		return EXIT_FAILURE;
	}
	for	(int i = 0; i < 5; i++) {
		if (pthread_create(&thread_list[i], NULL, &routine, (void *)&i) != 0) {
			perror("Failed to create thread");
			pthread_mutex_destroy(&mutex);
			return EXIT_FAILURE;
		}
		printf("Thread %d created\n", i + 1);
	}
	for	(int i = 0; i < 5; i++) {
		if (pthread_join(thread_list[i],	(void **)&result) != 0) {
			perror("Failed to join thread");
			pthread_mutex_destroy(&mutex);
			return EXIT_FAILURE;
		}
		printf("Thread %d joined\n", i + 1);
	}
	printf("Main value: %d\n", *result);
	pthread_mutex_destroy(&mutex);
	printf("Final value of x = %d\n", x);
	return EXIT_SUCCESS;
}