/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 16:36:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

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
	TAKEN_FORKS,
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_status;

#endif