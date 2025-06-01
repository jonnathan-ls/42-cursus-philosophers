/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:48:17 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/07 21:21:55 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKEN_FORKS);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKEN_FORKS);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKEN_FORKS);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKEN_FORKS);
	}
}

void	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, EATING);
	sleep_in_ms(table->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	print_status(philo, SLEEPING);
	sleep_in_ms(table->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINKING);
	sleep_in_ms(1);
}
