/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 16:24:19 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "macros.h"
# include "structs.h"
# include <errno.h>

void	*routine(void *arg);

void	init_table(t_table *table);
void	init_args(t_table *table, int argc, char **argv);
void	init_philos(t_table *table);
long	ft_atol(const char *nptr);
void	free_memory(t_table *table);
void	*monitor_routine(void *arg);
size_t	get_current_time_in_ms(void);
void	free_resources(t_table *table);
void	stop_simulation(t_table *table);
void	destroy_mutexes(t_table *table);
t_bool	should_continue(t_table *table);
void	*monitor(void *arg);
int		sleep_in_ms( size_t milissegundos);
void	exit_with_error(char *msg, t_table *table);
void	print_status(t_philo *philo, t_status status);

#endif