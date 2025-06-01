/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 16:36:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

static t_bool	take_forks(t_philo *philo, t_table *table,
	pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	*first_fork = philo->left_fork;
	*second_fork = philo->right_fork;
	if (philo->left_fork >= philo->right_fork)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	pthread_mutex_lock(*first_fork);
	print_status(philo, TAKEN_FORKS);
	if (!should_continue(table))
	{
		pthread_mutex_unlock(*first_fork);
		return (FALSE);
	}
	pthread_mutex_lock(*second_fork);
	print_status(philo, TAKEN_FORKS);
	if (!should_continue(table))
	{
		pthread_mutex_unlock(*second_fork);
		pthread_mutex_unlock(*first_fork);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	process_actions(t_philo *philo, t_table *table)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	print_status(philo, THINKING);
	if (!take_forks(philo, table, &first_fork, &second_fork))
		return (FALSE);
	pthread_mutex_lock(&table->philo_mutex);
	philo->last_meal_time = get_current_time_in_ms();
	pthread_mutex_unlock(&table->philo_mutex);
	print_status(philo, EATING);
	sleep_in_ms(table->time_to_eat);
	pthread_mutex_lock(&table->philo_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->philo_mutex);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	print_status(philo, SLEEPING);
	sleep_in_ms(table->time_to_sleep);
	return (TRUE);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_table			*table;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 != 0)
		sleep_in_ms(1);
	while (should_continue(table))
		if (!process_actions(philo, table))
			return (NULL);
	return (NULL);
}
