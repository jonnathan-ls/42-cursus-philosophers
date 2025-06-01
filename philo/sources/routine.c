/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/07 20:43:08 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

static void	process_actions(t_philo *philo)
{
	philo_take_forks(philo);
	philo_eat(philo);
	philo_release_forks(philo);
	philo_sleep(philo);
	philo_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	while (should_continue(philo->table))
		process_actions(philo);
	return (NULL);
}
