/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/24 18:02:43 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define NO_PHILOS 0
# define MAX_PHILOS 200
# define MILLISECOND 1000
# define MAX_TIME_IN_MS 60

# define COLOR_RESET "\033[0m"
# define COLOR_RED "\033[31m"
# define COLOR_GREEN "\033[32m"
# define COLOR_YELLOW "\033[33m"
# define COLOR_BLUE "\033[34m"
# define COLOR_MAGENTA "\033[35m"

# define DESCRIPTION_ERR_MSG	"Considerations: \n\t\
- <argument> means required arguments.\n\t\
- [argument] means optional arguments.\n\t\
- All arguments must be positive integers.\n\t\
- The number of philosophers must be greater than 0.\n"
# define INVALID_ARGS_ERR_MSG	"Error: Invalid arguments\n"
# define CORRECTLY_PROMPT_MSG	"Correctly prompt ./philo <number_of_philos> \
<time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]\n"
# define NUM_PHILOS_ERR_MSG	"Error: \
Number of philosophers must be greater than 0\n"
# define NUM_PHILOS_SIZE_ERR_MSG	"Error: \
Number of philosophers must be less than 200\n"
# define TIME_ARG_ERR_MSG	"Error: \
The timestamp arguments must be greater than 60ms\n"

# define GET_TIME_ERR_MSG	"Error: gettimeofday() failure\n"

#endif