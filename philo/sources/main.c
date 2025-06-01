/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 16:36:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (FALSE);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

static void	validate_args_values(t_table *table)
{
	if (table->num_philosophers == NO_PHILOS)
		exit_with_error(NUM_PHILOS_ERR_MSG, table);
	if (table->num_philosophers > MAX_PHILOS)
		exit_with_error(NUM_PHILOS_SIZE_ERR_MSG, table);
	if (table->time_to_die < MAX_TIME_IN_MS
		|| table->time_to_eat < MAX_TIME_IN_MS
		|| table->time_to_sleep < MAX_TIME_IN_MS)
		exit_with_error(TIME_ARG_ERR_MSG, table);
}

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

static void	execute_simulation(t_table *table)
{
	int		index;

	if (table->num_philosophers == 1)
	{
		print_status(&table->philos[0], TAKEN_FORKS);
		sleep_in_ms(table->time_to_die);
		print_status(&table->philos[0], DEAD);
		return ;
	}
	index = -1;
	while (++index < table->num_philosophers)
	{
		pthread_create(&table->philos[index].thread_id, NULL,
			routine, &table->philos[index]);
		pthread_create(&table->philos[index].monitor_id, NULL,
			monitor, &table->philos[index]);
		usleep(100);
	}
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
