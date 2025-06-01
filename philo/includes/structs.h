/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/31 21:38:43 by jlacerda         ###   ########.fr       */
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

typedef struct s_fork			t_fork;
typedef struct s_philo			t_philo;
typedef struct s_table			t_table;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_operation
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	JOIN,
	CREATE,
	DETACH,
}	t_operation;


typedef struct s_thread_arg
{
	void	*data;
	t_table	*table;
}	t_thread_arg;

typedef struct s_fork
{
	int				id;
	t_bool			is_available;
	pthread_mutex_t	*thread_mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;
typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meals_required;
	int				num_philosophers;
	long			start_dinner_time;
	t_bool			simulation_running;
}	t_table;

#endif