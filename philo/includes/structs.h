/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 14:50:22 by jlacerda         ###   ########.fr       */
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

typedef enum e_status
{
	TAKING_FORKS,
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_status;

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
	t_table			*table;
	t_bool			is_dead;
	pthread_t		thread_id;
	pthread_t		monitor_id;
	long			meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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