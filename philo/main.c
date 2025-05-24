/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/24 18:22:20 by jlacerda         ###   ########.fr       */
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
	table->start_dinner_time = get_current_time_in_ms();
}

static void	prepare_dining(t_table *table, int argc, char **argv)
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

	prepare_dining(&table, argc, argv);
	printf("args: %d %lu %lu %lu %d\n", table.amount_philos, table.time_to_die,
		table.time_to_eat, table.time_to_sleep, table.amount_limit_meals);
}
