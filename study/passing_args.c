
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include	<unistd.h>

int primes[]	= {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

void *print_prime_correct_but_disorderly_approach(void *arg)
{
	int index = *(int *)arg;
	printf("Prime number is: %d\n", primes[index]);
	free(arg); // Free the allocated memory for the argument
	return	NULL;
}

int main(void)
{
	pthread_t	thread_list[10];
	pthread_mutex_t mutex;
	int i;
	if (pthread_mutex_init(&mutex, NULL) != 0) {
		perror("Failed to initialize mutex");
		return EXIT_FAILURE;
	}
	for	(i = 0; i < 5; i++) {
		int* arg =	malloc(sizeof(int));
		*arg	= i; // Allocate memory for the argument and assign the index
		if (pthread_create(&thread_list[i], NULL, &print_prime_correct_but_disorderly_approach, (void *)arg) != 0) {
			perror("Failed to create thread");
			pthread_mutex_destroy(&mutex);
			return EXIT_FAILURE;
		}
	}
	for	(i = 0; i < 5; i++) {
		if (pthread_join(thread_list[i], NULL) != 0) {
			perror("Failed to join thread");
			pthread_mutex_destroy(&mutex);
			return EXIT_FAILURE;
		}
	}
	pthread_mutex_destroy(&mutex);
	return EXIT_SUCCESS;
}