/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/08 16:14:12 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_current_time_in_ms(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1) {
		printf(COLOR_RED GET_TIME_ERR_MSG COLOR_RESET);
		return (0);
	}
	if (time.tv_sec < 0 || time.tv_usec < 0) {
		printf(COLOR_RED TIME_EVAL_VALUES_ERR_MSG COLOR_RESET
			"tv_sec=%ld, tv_usec=%ld\n", time.tv_sec, time.tv_usec);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

uint64_t	sleep_in_ms(uint64_t time_ms)
{
	uint64_t	start_ms;
	uint64_t	elapsed_ms;
	uint64_t	current_time;

	if (time_ms == 0)
		return (0);
	start_ms = get_current_time_in_ms();
	while (TRUE)
	{
		usleep(time_ms / 10);
		current_time = get_current_time_in_ms();
		elapsed_ms = current_time - start_ms;
		if (elapsed_ms >= time_ms)
			break ;
	}
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

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (status == DEAD || should_continue(table))
	{
		timestamp = get_current_time_in_ms() - table->start_dinner_time;
		printf(get_status_message(TIMESTAMP), timestamp);
		printf(get_status_message(PHILO_ID), philo->id);
		printf("%s\n", get_status_message(status));
	}
	pthread_mutex_unlock(&table->print_mutex);
}
