/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/24 16:00:42 by jlacerda         ###   ########.fr       */
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
int	ft_usleep( size_t milissegundos)
{
	size_t	start;
	int		current_time;	

	current_time = 0;
	start = get_current_time_in_ms();
	while ((get_current_time_in_ms() - start) < milissegundos)
		current_time += usleep(500);
	return (current_time);
}
