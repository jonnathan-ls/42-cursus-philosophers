/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 14:52:45 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	t_table			*table;
	t_bool			forks_taken;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (!arg)
		return (NULL);
	forks_taken = FALSE;
	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 != 0)
		sleep_in_ms(1);
	while (should_continue(table))
	{
		print_status(philo, THINKING);
		if (philo->left_fork < philo->right_fork)
		{
						first_fork = philo->left_fork;
						second_fork = philo->right_fork;
		}
		else
		{
						first_fork = philo->right_fork;
						second_fork = philo->left_fork;
		}
		pthread_mutex_lock(first_fork);
		print_status(philo, TAKING_FORKS);
		if (!should_continue(table))
		{
			pthread_mutex_unlock(first_fork);
			return (NULL);
		}
		pthread_mutex_lock(second_fork);
		print_status(philo, TAKING_FORKS);
		if (!should_continue(table))
		{
			pthread_mutex_unlock(second_fork);
			pthread_mutex_unlock(first_fork);
			return (NULL);
		}
		forks_taken = TRUE;
		pthread_mutex_lock(&table->death_mutex);
		philo->last_meal_time = get_current_time_in_ms();
		pthread_mutex_unlock(&table->death_mutex);
		print_status(philo, EATING);
		sleep_in_ms(table->time_to_eat);
		pthread_mutex_lock(&table->death_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&table->death_mutex);
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		forks_taken = FALSE;
		print_status(philo, SLEEPING);
		sleep_in_ms(table->time_to_sleep);
	}
	return (NULL);
}

void	*monitor_single_philo(void *arg)
{
	t_philo		*philo;
	t_table		*table;
	uint64_t	time_since_last_meal;

	philo = (t_philo *)arg;
	table = philo->table;
	while (should_continue(table))
	{
		pthread_mutex_lock(&table->death_mutex);
		time_since_last_meal = get_current_time_in_ms() - philo->last_meal_time;
		if (time_since_last_meal > table->time_to_die)
		{
			philo->is_dead = TRUE;
			table->simulation_running = FALSE;
			pthread_mutex_unlock(&table->death_mutex);
			print_status(philo, DEAD);
			return (NULL);
		}
		pthread_mutex_unlock(&table->death_mutex);
		pthread_mutex_lock(&table->death_mutex);
		if (table->meals_required > 0
			&& philo->meals_eaten >= table->meals_required)
		{
			pthread_mutex_unlock(&table->death_mutex);
			stop_simulation(table);
			return (NULL);
		}
		pthread_mutex_unlock(&table->death_mutex);
		usleep(1000);
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
				print_status(philo, DEAD);
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
				stop_simulation(table);
				return (NULL);
			}
		}
		sleep_in_ms(1);
	}
	return (NULL);
}
