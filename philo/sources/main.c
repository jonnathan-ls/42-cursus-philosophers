/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/13 21:25:19 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Validates the command line arguments.
 * Checks if the number of arguments is correct,
 * and if each argument is a valid positive integer.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return TRUE if the arguments are valid, FALSE otherwise.
 */
static void	validate_args_values(t_table *table)
{
	if (table->num_philosophers == NO_PHILOS)
		exit_with_error(NUM_PHILOS_ERR_MSG, table);
	if (table->num_philosophers > MAX_PHILOS)
		exit_with_error(NUM_PHILOS_SIZE_ERR_MSG, table);
	if (table->time_to_die < MIN_TIME_IN_MS
		|| table->time_to_eat < MIN_TIME_IN_MS
		|| table->time_to_sleep < MIN_TIME_IN_MS
		|| table->time_to_die > INT_MAX
		|| table->time_to_eat > INT_MAX
		|| table->time_to_sleep > INT_MAX)
		exit_with_error(TIME_ARG_ERR_MSG, table);
	printf("meals_required: %ld\n", table->meals_required);
	if (table->meals_required == 0 || table->meals_required > INT_MAX)
		exit_with_error(MEALS_REQUIRED_ERR_MSG, table);
}

/**
 * @brief Prepares the dinner by initializing the forks and philosophers.
 * Allocates memory for the forks and philosophers,
 * initializes the print and philosopher mutexes,
 * and sets the start dinner time to the current time.
 * @param table Pointer to the table struct.
 * @note This function allocates memory for the forks and philosophers,
 * and initializes the mutexes used for synchronization.
 * If memory allocation fails, it exits with an error message.
 */
static void	prepare_dinner(t_table *table)
{
	int	index;

	index = -1;
	table->start_dinner_time = get_current_time_in_ms();
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	table->philos = malloc(sizeof(t_philo) * table->num_philosophers);
	if (!table->forks || !table->philos)
		exit_with_error(MALLOC_ERR_MSG, table);
	while (++index < table->num_philosophers)
		pthread_mutex_init(&table->forks[index], NULL);
}

/**
 * @brief Creates threads for each philosopher.
 * Each philosopher is assigned a thread that runs the philo_routine function.
 * If thread creation fails, it prints an error message and returns FALSE.
 * @param table Pointer to the table struct containing the philosophers.
 * @return TRUE if all threads are created successfully, FALSE otherwise.
 */
static t_bool	create_threads(t_table *table)
{
	int	index;
	int	status;

	index = -1;
	while (++index < table->num_philosophers)
	{
		status = pthread_create(&table->philos[index].thread_id,
				NULL, philo_routine, &table->philos[index]);
		if (status != 0)
		{
			printf(COLOR_RED THREAD_CREATE_ERR_MSG COLOR_RESET);
			return (FALSE);
		}
	}
	return (TRUE);
}

/**
 * @brief Executes the simulation by creating threads for each philosopher
 * and starting the monitor thread.
 * Waits for all philosopher threads to finish before exiting.
 * @param table Pointer to the table struct containing the philosophers.
 */
static void	execute_simulation(t_table *table)
{
	int			index;
	pthread_t	monitor_thread;

	if (!create_threads(table))
		return ;
	pthread_create(&monitor_thread, NULL,
		(void *(*)(void *))monitor_philos, table);
	index = -1;
	while (++index < table->num_philosophers)
		pthread_join(table->philos[index].thread_id, NULL);
	pthread_join(monitor_thread, NULL);
}

/**
 * @brief Main function of the philosopher simulation.
 * Initializes the table, validates the command line arguments,
 * prepares the dinner by initializing forks and philosophers,
 * and executes the simulation.
 */
int	main(int argc, char **argv)
{
	t_table	table;

	init_table(&table);
	if (!is_valid_args(argc, argv))
	{
		printf(COLOR_RED INVALID_ARGS_ERR_MSG COLOR_RESET);
		printf(COLOR_YELLOW CORRECTLY_PROMPT_MSG COLOR_RESET);
		printf(DESCRIPTION_ERR_MSG);
		exit_with_error(NULL, &table);
	}
	init_args(&table, argc, argv);
	validate_args_values(&table);
	prepare_dinner(&table);
	init_philos(&table);
	execute_simulation(&table);
	free_resources(&table);
	return (EXIT_SUCCESS);
}
