/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 14:50:59 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "macros.h"
# include "structs.h"
# include <errno.h>

void	*routine(void *arg);
long	ft_atol(const char *nptr);
void	free_memory(t_table *table);
void	*monitor_routine(void *arg);
size_t	get_current_time_in_ms(void);
void	free_resources(t_table *table);
void	stop_simulation(t_table *table);
void	destroy_mutexes(t_table *table);
t_bool	should_continue(t_table *table);
void	*monitor_single_philo(void *arg);
int		sleep_in_ms( size_t milissegundos);
void	exit_with_error(char *msg, t_table *table);
void	print_status(t_philo *philo, t_status status);
long	get_long(pthread_mutex_t *mutex, long *value);
t_bool	get_bool(pthread_mutex_t *mutex, t_bool *value);
void	set_long(pthread_mutex_t *mutex, long *var, long value);
void	set_bool(pthread_mutex_t *mutex, t_bool *var, t_bool value);

#endif