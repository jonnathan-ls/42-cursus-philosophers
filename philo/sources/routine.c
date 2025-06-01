/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/31 21:47:50 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	t_bool	forks_taken;

	if (!arg)
		return (NULL);
	forks_taken = FALSE;
	philo = (t_philo *)arg;
	table = philo->table;
	while (should_continue(table))
	{
		print_status(philo, "is thinking");
		if (philo->id % 2 != 0)
			sleep_in_ms(1);
		pthread_mutex_lock(philo->left_fork);
		if (!should_continue(table))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		if (!should_continue(table))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (NULL);
		}
		print_status(philo, "has taken a fork");
		forks_taken = TRUE;
		pthread_mutex_lock(&table->death_mutex);
		philo->last_meal_time = get_current_time_in_ms();
		pthread_mutex_unlock(&table->death_mutex);
		print_status(philo, "is eating");
		sleep_in_ms(table->time_to_eat);
		pthread_mutex_lock(&table->death_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&table->death_mutex);
		if (forks_taken)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			forks_taken = FALSE;
		}
		print_status(philo, "is sleeping");
		sleep_in_ms(table->time_to_sleep);
	}
	if (forks_taken) {
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	uint64_t	time_since_last_meal;
	t_bool		all_ate_enough;
	t_philo		*philo;
	t_table		*table;
	int			i;

	if (!arg)
		return (NULL);
	table = (t_table *)arg;
	while (TRUE)
	{
		i = -1;
		while (++i < table->num_philosophers)
		{
			pthread_mutex_lock(&table->death_mutex);
			philo = &table->philos[i];
			time_since_last_meal = get_current_time_in_ms()
				- table->philos[i].last_meal_time;
			if (time_since_last_meal > table->time_to_die)
			{
				stop_simulation(table);
				pthread_mutex_unlock(&table->death_mutex);
				print_status(philo, "died");
				return (NULL);
			}
			pthread_mutex_unlock(&table->death_mutex);
		}

		if (table->meals_required > 0)
		{
			all_ate_enough = TRUE;
			i = -1;
			while (++i < table->num_philosophers)
			{
				pthread_mutex_lock(&table->death_mutex);
				if (table->philos[i].meals_eaten < table->meals_required)
				{
					all_ate_enough = FALSE;
					pthread_mutex_unlock(&table->death_mutex);
					break ;
				}
				pthread_mutex_unlock(&table->death_mutex);
			}
			if (all_ate_enough)
			{
				pthread_mutex_lock(&table->death_mutex);
				table->simulation_running = FALSE;
				pthread_mutex_unlock(&table->death_mutex);
				return (NULL);
			}
		}
		sleep_in_ms(1);
	}

	return (NULL);
}
