/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/07 21:01:10 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# include "enums.h"

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	t_table			*table;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	int				meals_eaten;
	uint64_t		last_meal_time;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	philo_mutex;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meals_required;
	int				num_philosophers;
	uint64_t		start_dinner_time;
	t_bool			dinner_in_progress;
}	t_table;

#endif