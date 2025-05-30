/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/26 21:46:35 by jlacerda         ###   ########.fr       */
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

static void	init_table(t_table *table)
{
	table->forks = NULL;
	table->philos = NULL;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->amount_philos = 0;
	table->start_dinner_time = 0;
	table->is_dinner_over = FALSE;
	table->amount_limit_meals = -1;
	table->all_threads_ready_created = FALSE;
}

static void	prepare_table(t_table *table, int argc, char **argv)
{
	table->amount_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->amount_limit_meals = ft_atol(argv[5]);
	else
		table->amount_limit_meals = -1;
}

static void init_philos(t_table *table)
{
	int		index_philo;
	int		index_fork;
	t_philo	*philo;

	index_philo = -1;
	while (++index_philo < table->amount_philos)
	{
		philo = table->philos + index_philo;
		philo->table = table;
		philo->thread_id = -1;
		philo->meals_eaten = 0;
		philo->last_meal_time = -1;
		philo->id = index_philo + 1;
		philo->is_satisfied = FALSE;
		philo->right_fork = &table->forks[index_philo];
		index_fork = (index_philo + 1) % table->amount_philos;
		philo->left_fork = &table->forks[index_fork];
		if (philo->id % 2 == 0)
		{
			philo->left_fork = &table->forks[index_philo];
			index_fork = (index_philo + 1) % table->amount_philos;
			philo->right_fork = &table->forks[index_fork];
		}
	}
}

static void	prepare_dinner(t_table *table)
{
	int	index;

	index = -1;
	table->start_dinner_time = get_current_time_in_ms();
	table->forks = safe_malloc(sizeof(t_fork) * table->amount_philos, table);
	table->philos = safe_malloc(sizeof(t_philo) * table->amount_philos, table);
	safe_mutex(INIT, &table->ready_mutex, table);
	while (++index < table->amount_philos)
	{
		table->forks[index].id = index;
		table->forks[index].thread_mutex = safe_malloc(sizeof(pthread_mutex_t), table);
		safe_mutex(INIT, table->forks[index].thread_mutex, table);
	}
	init_philos(table);
}

static void	validate_args(t_table *table, int argc, char **argv)
{
	init_table(table);
	if (!is_valid_args(argc, argv))
	{
		printf(COLOR_RED INVALID_ARGS_ERR_MSG COLOR_RESET);
		printf(COLOR_YELLOW CORRECTLY_PROMPT_MSG COLOR_RESET);
		printf(DESCRIPTION_ERR_MSG);
		exit_with_error(NULL, table);
	}
	prepare_table(table, argc, argv);
	if (table->amount_philos == NO_PHILOS)
		exit_with_error(NUM_PHILOS_ERR_MSG, table);
	if (table->amount_philos > MAX_PHILOS)
		exit_with_error(NUM_PHILOS_SIZE_ERR_MSG, table);
	if (table->time_to_die < MAX_TIME_IN_MS
		|| table->time_to_eat < MAX_TIME_IN_MS
		|| table->time_to_sleep < MAX_TIME_IN_MS)
		exit_with_error(TIME_ARG_ERR_MSG, table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	validate_args(&table, argc, argv);
	printf("args: %d %lu %lu %lu %d\n", table.amount_philos, table.time_to_die,
		table.time_to_eat, table.time_to_sleep, table.amount_limit_meals);
	prepare_dinner(&table);
	int i = 0;
	while (i < table.amount_philos)
	{
		printf("forks[%d] = %d\n", i, table.forks[i].id);
		i++;
	}
	i = 0;
	while (i < table.amount_philos)
	{
		printf("philos[%d] = %d\n", i, table.philos[i].id);
		printf("left_fork[%d] = %d\n", i, table.philos[i].left_fork->id);
		printf("right_fork[%d] = %d\n", i, table.philos[i].right_fork->id);
		printf("meals_eaten[%d] = %ld\n", i, table.philos[i].meals_eaten);
		printf("last_meal_time[%d] = %ld\n", i, table.philos[i].last_meal_time);
		printf("is_satisfied[%d] = %d\n", i, table.philos[i].is_satisfied);
		printf("thread_id[%d] = %ld\n", i, table.philos[i].thread_id);
		printf("table[%d] = %p\n", i, (void *)table.philos[i].table);
		i++;
	}
}
