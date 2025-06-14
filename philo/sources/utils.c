/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/13 21:31:46 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

/**
 * @brief Checks if the command line arguments are valid.
 * Validates the number of arguments and checks if each argument
 * is a positive integer or a positive integer with a '+' sign.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return TRUE if the arguments are valid, FALSE otherwise.
 * @note The function checks if the number of arguments is between 5 and 6,
 * and if each argument is a valid positive integer.
 * It returns FALSE if any argument is invalid or if the number of arguments
 * is not within the expected range.
 */
int	is_valid_args(int argc, char **argv)
{
	int	i;
	int	j;
	int	len;

	if (argc < 5 || argc > 6)
		return (FALSE);
	i = 1;
	while (i < argc)
	{
		j = 0;
		len = 0;
		while (argv[i][len])
			len++;
		if (len == 0 || len > INT_SIZE_LENGTH)
			return (FALSE);
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

/**
 * @brief Exits the program with an error message.
 * This function prints the provided error message in red,
 * frees the resources allocated for the table struct,
 * and then exits the program with a failure status.
 * @param msg The error message to print.
 * @param table Pointer to the table struct to free resources for.
 * @note If the msg is NULL, it will not print any message.
 */
void	exit_with_error(char	*msg, t_table *table)
{
	if (msg)
		printf(COLOR_RED "%s" COLOR_RESET, msg);
	free_resources(table);
	exit(EXIT_FAILURE);
}

/**
 * @brief Frees the resources allocated for the table struct.
 * Destroys the mutexes for forks and philosophers,
 * and frees the memory allocated for forks and philosophers.
 * @param table Pointer to the table struct to free resources for.
 */
void	free_resources(t_table *table)
{
	int	index;

	if (!table)
		return ;
	if (table->forks)
	{
		index = -1;
		while (++index < table->num_philosophers)
		{
			pthread_mutex_destroy(&table->forks[index]);
			pthread_mutex_destroy(&table->philos[index].meal_mutex);
		}
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->philo_mutex);
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

/**
 * @brief Returns a status message based on the philosopher's action.
 * This function returns a string that describes the current status
 * of a philosopher based on the provided status enum.
 * It includes colored messages for better visibility
 * and can switch to plain text messages if CSS is disabled.
 * @param status The status of the philosopher.
 * @return A string representing the status message.
 * @note The function uses an array of strings to map each status
 * to its corresponding message.
 */
char	*get_status_message(t_status status)
{
	char	*messages[7];

	messages[TAKEN_FORKS] = " 🍴 has taken a fork";
	messages[DEAD] = COLOR_RED " ☠️  died" COLOR_RESET;
	messages[TIMESTAMP] = COLOR_CYAN "⏱️  %ld" COLOR_RESET;
	messages[PHILO_ID] = COLOR_MAGENTA " 🧛 %-3d" COLOR_RESET;
	messages[EATING] = COLOR_GREEN " 🍝 is eating" COLOR_RESET;
	messages[SLEEPING] = COLOR_BLUE " 🛌 is sleeping" COLOR_RESET;
	messages[THINKING] = COLOR_YELLOW " 💭 is thinking" COLOR_RESET;
	if (!CSS)
	{
		messages[DEAD] = " died";
		messages[PHILO_ID] = " %d";
		messages[TIMESTAMP] = "%ld";
		messages[EATING] = " is eating";
		messages[THINKING] = " is thinking";
		messages[SLEEPING] = " is sleeping";
		messages[TAKEN_FORKS] = " has taken a fork";
	}
	return (messages[status]);
}
