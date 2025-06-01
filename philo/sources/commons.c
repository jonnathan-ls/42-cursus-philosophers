/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/07 21:07:48 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_current_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf(COLOR_RED GET_TIME_ERR_MSG COLOR_RESET);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

uint64_t	sleep_in_ms(uint64_t time_ms)
{
	uint64_t	start;

	if (time_ms == 0)
		return (0);
	start = get_current_time_in_ms();
	while (get_current_time_in_ms() - start < time_ms)
		usleep(time_ms / 10);
	return (get_current_time_in_ms());
}

t_bool	should_continue(t_table *table)
{
	t_bool	result;

	if (!table)
		return (FALSE);
	pthread_mutex_lock(&table->philo_mutex);
	result = table->dinner_in_progress;
	pthread_mutex_unlock(&table->philo_mutex);
	return (result);
}

void	stop_simulation(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_lock(&table->philo_mutex);
	table->dinner_in_progress = FALSE;
	pthread_mutex_unlock(&table->philo_mutex);
}

void	print_status(t_philo *philo, t_status status)
{
	t_table		*table;
	uint64_t	timestamp;
	static char	*status_strs[] = {
		"has taken a fork",
		COLOR_YELLOW "is thinking" COLOR_RESET,
		COLOR_GREEN "is eating" COLOR_RESET,
		COLOR_BLUE "is sleeping"	COLOR_RESET,
		COLOR_RED "died" COLOR_RESET,
	};

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (should_continue(table) && status != DEAD)
	{
		timestamp = get_current_time_in_ms() - table->start_dinner_time;
		printf(COLOR_CYAN "%ld" COLOR_RESET " %d %s\n",
			timestamp, philo->id, status_strs[status]);
	}
	pthread_mutex_unlock(&table->print_mutex);
}
