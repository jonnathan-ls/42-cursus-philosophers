/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/24 18:15:56 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_with_error(char	*msg, t_table *table)
{
	if (msg)
		printf(COLOR_RED "%s" COLOR_RESET, msg);
	if (table)
	{
		if (table->forks)
			free(table->forks);
		if (table->philos)
			free(table->philos);
	}
	exit(EXIT_FAILURE);
}
