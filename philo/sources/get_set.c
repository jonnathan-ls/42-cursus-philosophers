/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/26 21:44:11 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, t_bool *var, t_bool value)
{
	safe_mutex(LOCK, mutex, NULL);
	*var = value;
	safe_mutex(UNLOCK, mutex, NULL);
}

t_bool	get_bool(pthread_mutex_t *mutex, t_bool *value)
{
	t_bool	result;

	safe_mutex(LOCK, mutex, NULL);
	result = *value;
	safe_mutex(UNLOCK, mutex, NULL);
	return (result);
}

void	set_long(pthread_mutex_t *mutex, long *var, long value)
{
	safe_mutex(LOCK, mutex, NULL);
	*var = value;
	safe_mutex(UNLOCK, mutex, NULL);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	result;

	safe_mutex(LOCK, mutex, NULL);
	result = *value;
	safe_mutex(UNLOCK, mutex, NULL);
	return (result);
}

t_bool	is_simulation_finished(t_table *table)
{
	t_bool	is_finished;

	is_finished = get_bool(&table->ready_mutex, &table->is_dinner_over);
	return (is_finished);
}
