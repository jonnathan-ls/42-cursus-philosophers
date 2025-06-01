/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 17:13:36 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	prepare_dinner(t_table *table)
{
	int	index;

	index = -1;
	table->forks = malloc(sizeof(t_fork) * table->num_philosophers);
	table->philos = malloc(sizeof(t_philo) * table->num_philosophers);
	if (!table->forks || !table->philos)
		exit_with_error(MALLOC_ERR_MSG, table);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->philo_mutex, NULL);
	while (++index < table->num_philosophers)
		pthread_mutex_init(&table->forks[index], NULL);
}

static t_bool	create_threads(t_table *table)
{
	int	index;
	int	status;

	index = -1;
	while (++index < table->num_philosophers)
	{
		status = pthread_create(&table->philos[index].thread_id,
				NULL, routine, &table->philos[index]);
		if (status != 0)
		{
			printf(COLOR_RED THREAD_CREATE_ERR_MSG COLOR_RESET);
			return (FALSE);
		}
		pthread_create(&table->philos[index].monitor_id, NULL,
			monitor, &table->philos[index]);
		if (table->num_philosophers > 50)
			usleep(500);
		else
			usleep(100);
	}
	return (TRUE);
}

static void	execute_simulation(t_table *table)
{
	int	index;

	table->start_dinner_time = get_current_time_in_ms();
	if (table->num_philosophers == 1)
	{
		print_status(&table->philos[0], TAKEN_FORKS);
		sleep_in_ms(table->time_to_die);
		print_status(&table->philos[0], DEAD);
		return ;
	}
	if (!create_threads(table))
		return ;
	index = -1;
	while (++index < table->num_philosophers)
	{
		pthread_join(table->philos[index].thread_id, NULL);
		pthread_join(table->philos[index].monitor_id, NULL);
	}
}

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
