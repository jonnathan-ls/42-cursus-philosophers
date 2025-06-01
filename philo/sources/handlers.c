/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 14:51:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// static char	*process_mutex_handler(int status, t_operation operation)
// {
// 	if (status == 0)
// 		return (NULL);
// 	if (status == EINVAL && (operation == LOCK || operation == UNLOCK))
// 		return (MUTEX_INVALID_ERR_MSG);
// 	else if (status == EINVAL && operation == INIT)
// 		return (ATTR_INVALID_ERR_MSG);
// 	else if (status == EDEADLK)
// 		return (DEADLOCK_ERR_MSG);
// 	else if (status == ENOMEM)
// 		return (CREATE_ANOTHER_ERR_MSG);
// 	else if (status == EBUSY)
// 		return (MUTEX_IS_BUSY_ERR_MSG);
// 	return (NULL);
// }

// static char	*process_thread_handler(int status, t_operation operation)
// {
// 	if (status == 0)
// 		return (NULL);
// 	if (status == EAGAIN)
// 		return (THREAD_RESOURCES_ERR_MSG);
// 	else if (status == EPERM)
// 		return (THREAD_PERMISSION_ERR_MSG);
// 	else if (status == EINVAL && operation == CREATE)
// 		return (ATTR_INVALID_ERR_MSG);
// 	else if (status == EINVAL && (operation == JOIN || operation == DETACH))
// 		return (THREAD_JOIN_ERR_MSG);
// 	else if (status == ESRCH)
// 		return (THREAD_ID_ERR_MSG);
// 	else if (status == EDEADLK)
// 		return (THREAD_DEADLOCK_ERR_MSG);
// 	return (NULL);
// }

// int	safe_mutex(t_operation operation, pthread_mutex_t *mutex)
// {
// 	char	*err;

// 	if (!mutex)
// 	{
// 		printf(COLOR_RED MUTEX_ERR_MSG COLOR_RESET);
// 		return (FAILURE);
// 	}
// 	err = NULL;
// 	if (operation == INIT)
// 		err = process_mutex_handler(pthread_mutex_init(mutex, NULL), operation);
// 	else if (operation == LOCK)
// 		err = process_mutex_handler(pthread_mutex_lock(mutex), operation);
// 	else if (operation == UNLOCK)
// 		err = process_mutex_handler(pthread_mutex_unlock(mutex), operation);
// 	else if (operation == DESTROY)
// 		err = process_mutex_handler(pthread_mutex_destroy(mutex), operation);
// 	if (err)
// 	{
// 		printf(COLOR_RED "%s" COLOR_RESET, err);
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

// int	safe_thread(t_operation operation,
// 	pthread_t *thread, void *(*function)(void	*), t_thread_arg *t_arg)
// {
// 	char	*err;

// 	if (!thread || !t_arg || !t_arg->table)
// 	{
// 		printf(COLOR_RED THREAD_OPERATION_ERR_MSG COLOR_RESET);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (operation == CREATE)
// 		err = process_thread_handler(pthread_create(thread,
// 					NULL, function, t_arg->data), operation);
// 	else if (operation == JOIN)
// 		err = process_thread_handler(pthread_join(*thread, NULL), operation);
// 	else if (operation == DETACH)
// 		err = process_thread_handler(pthread_detach(*thread), operation);
// 	else
// 		err = THREAD_OPERATION_ERR_MSG;
// 	if (err)
// 	{
// 		printf(COLOR_RED "%s" COLOR_RESET, err);
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }
