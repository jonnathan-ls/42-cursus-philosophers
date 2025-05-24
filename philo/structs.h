/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/24 18:12:21 by jlacerda         ###   ########.fr       */
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

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	*fork;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_table			*table;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			meals_eaten;
	t_bool			is_satisfied;
	long			last_meal_time;

	pthread_t		thread_id;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
}	t_philo;

typedef struct s_table
{
	t_fork		*forks;
	t_philo		*philos;
	int			amount_philos;
	int			amount_limit_meals;
	long		start_dinner_time;
	t_bool		is_dinner_over;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
}	t_table;

#endif