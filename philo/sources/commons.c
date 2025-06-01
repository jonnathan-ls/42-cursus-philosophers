/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/31 21:32:31 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Gets the current time in milliseconds.
 * @return The current time in milliseconds.
 */
size_t	get_current_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf(COLOR_RED GET_TIME_ERR_MSG COLOR_RESET);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief Sleeps for a specified number of milliseconds.
 * @return The current time in milliseconds.
 */
int	sleep_in_ms( size_t miliseconds)
{
	size_t	start;
	int		current_time;	

	current_time = 0;
	start = get_current_time_in_ms();
	while ((get_current_time_in_ms() - start) < miliseconds)
		current_time += usleep(100);
	return (current_time);
}

t_bool	should_continue(t_table *table)
{
	t_bool	result;

	if (!table)
		return (FALSE);
	pthread_mutex_lock(&table->death_mutex);
	result = table->simulation_running;
	pthread_mutex_unlock(&table->death_mutex);
	return (result);
}

void	stop_simulation(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_lock(&table->death_mutex);
	table->simulation_running = FALSE;
	pthread_mutex_unlock(&table->death_mutex);
}

void	print_status(t_philo *philo, char *status)
{
	long	current_time;
	t_table	*table;

	if (!philo || !status)
		return ;
	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	current_time = get_current_time_in_ms() - table->start_dinner_time;
	printf("%lu %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(&table->print_mutex);
}

// void	take_forks(t_philo *philo)
// {
// 	t_table	*table;

// 	if (!philo || philo->table)
// 		return ;
// 	table = philo->table;
// 	if (!should_continue(table))
// 		return ;
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_status(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->right_fork);
// 		print_status(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		print_status(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->left_fork);
// 		print_status(philo, "has taken a fork");
// 	}
// }


