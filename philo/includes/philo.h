/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/26 21:49:28 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "macros.h"
# include "structs.h"
# include <errno.h>

long		ft_atol(const char *nptr);
size_t		get_current_time_in_ms(void);
int			ft_usleep( size_t milissegundos);
void		exit_with_error(char *msg, t_table *table);

void	*safe_malloc(size_t size, t_table *table);
void	safe_mutex(t_operation operation,
	pthread_mutex_t *mutex, t_table *table);
void	safe_thread(t_operation operation,
	pthread_t *thread, void *(*function)(void	*), t_table *table);


// Setters and Getters
void	set_bool(pthread_mutex_t *mutex, t_bool *var, t_bool value);
t_bool	get_bool(pthread_mutex_t *mutex, t_bool *value);
void	set_long(pthread_mutex_t *mutex, long *var, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
t_bool	is_simulation_finished(t_table *table);

#endif