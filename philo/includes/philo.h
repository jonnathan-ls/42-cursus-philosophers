/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/12 21:18:31 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include "macros.h"
# include "structs.h"

void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_take_forks(t_philo *philo);
void		philo_release_forks(t_philo *philo);

void		*philo_routine(void *arg);
void		init_table(t_table *table);
void		init_philos(t_table *table);
long		ft_atol(const char *nptr);
size_t		get_current_time_in_ms(void);
void		free_resources(t_table *table);
void		*monitor_philos(t_table *table);
void		stop_simulation(t_table *table);
uint64_t	sleep_in_ms(uint64_t time_ms);
t_bool		should_continue(t_table *table);
char		*get_status_message(t_status status);
int			is_valid_args(int argc, char **argv);
void		exit_with_error(char	*msg, t_table *table);
void		print_status(t_philo *philo, t_status status);
void		init_args(t_table *table, int argc, char **argv);

#endif