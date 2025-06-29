/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/14 11:20:08 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# ifndef CSS
#  define CSS 1
# endif

# define SUCCESS 0
# define FAILURE 1
# define NO_PHILOS 0
# define MAX_PHILOS 200
# define MIN_TIME_IN_MS 60
# define INT_SIZE_LENGTH 11
# define INT_MAX 2147483647
# define MARGIN_ERR_DEAD_MS 5

# define COLOR_RED "\033[31m"
# define COLOR_CYAN "\033[36m"
# define COLOR_BLUE "\033[34m"
# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"
# define COLOR_YELLOW "\033[33m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_ORANGE "\033[38;5;208m"

# define MALLOC_ERR_MSG	"Error: malloc failed\n"
# define MUTEX_ERR_MSG	"Error: Mutex operation failed\n"

# define DESCRIPTION_ERR_MSG	"Considerations: \n     \
- <argument> means required arguments.\n     \
- [argument] means optional arguments.\n     \
- All arguments must be positive integers.\n"
# define INVALID_ARGS_ERR_MSG	"Error: Invalid arguments\n"
# define CORRECTLY_PROMPT_MSG	"Correctly prompt ./philo <number_of_philos> \
<time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]\n"
# define NUM_PHILOS_ERR_MSG	"Error: \
Number of philosophers must be greater than 0\n"
# define NUM_PHILOS_SIZE_ERR_MSG	"Error: \
Number of philosophers must be less than 200\n"
# define TIME_ARG_ERR_MSG	"Error: \
The timestamp arguments must be greater than 60ms \
and less than or equal to INT_MAX\n"
# define MEALS_REQUIRED_ERR_MSG	"Error: \
The number of meals required must be greater than 0 \
and less than or equal to INT_MAX\n"
# define THREAD_CREATE_ERR_MSG	"Error: pthread_create() failure\n"
# define GET_TIME_ERR_MSG	"Error: gettimeofday() failure\n"
# define TIME_EVAL_VALUES_ERR_MSG	"Error: timeval values are invalid "
/* ******************************************************************** */
# define MUTEX_INVALID_ERR_MSG	"The value specified by mutex is invalid\n"
# define ATTR_INVALID_ERR_MSG	"The value specified by attr is invalid\n"
# define DEADLOCK_ERR_MSG	"A deadlock \
would occur if the thread blocked waiting for the mutex\n"
# define CREATE_ANOTHER_ERR_MSG	"The process \
cannot allocate enough memory to create another mutex\n"
# define MUTEX_IS_BUSY_ERR_MSG	"The mutex is already locked\n"
/* ********************************************************************* */
# define THREAD_RESOURCES_ERR_MSG "No resources to create another thread\n"
# define THREAD_PERMISSION_ERR_MSG "\
The caller does not have appropriate permission\n"
# define THREAD_JOIN_ERR_MSG "\
The value specified by thread is not a joinable thread\n"
# define THREAD_ID_ERR_MSG "No thread could be found corresponding \
to that specified by the given thread ID\n"
# define THREAD_DEADLOCK_ERR_MSG "A deadlock was detected \
or the value of thread specified the calling thread\n"
# define THREAD_OPERATION_ERR_MSG "Wrong operation for thread handler\n"

#endif