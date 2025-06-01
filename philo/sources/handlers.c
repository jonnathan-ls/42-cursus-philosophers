/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 15:42:27 by jlacerda         ###   ########.fr       */
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

// char	*mutex_handler(t_operation operation, pthread_mutex_t *mutex)
// {
// 	if (!mutex)
// 		return (MUTEX_ERR_MSG);
// 	if (operation == INIT)
// 		return (process_mutex_handler(
// 				pthread_mutex_init(mutex, NULL), operation));
// 	else if (operation == LOCK)
// 		return (process_mutex_handler(pthread_mutex_lock(mutex), operation));
// 	else if (operation == UNLOCK)
// 		return (process_mutex_handler(pthread_mutex_unlock(mutex), operation));
// 	else if (operation == DESTROY)
// 		return (process_mutex_handler(pthread_mutex_destroy(mutex), operation));
// 	return (NULL);
// }

// char	*thread_handler(t_operation operation,
// 	pthread_t *thread, void *(*function)(void	*), t_thread_arg *t_arg)
// {
// 	if (!thread || !t_arg || !t_arg->table)
// 		return (THREAD_OPERATION_ERR_MSG);
// 	if (operation == CREATE)
// 		return (process_thread_handler(
// 				pthread_create(thread, NULL, function, t_arg->data),
// 				operation));
// 	else if (operation == JOIN)
// 		return (process_thread_handler(pthread_join(*thread, NULL), operation));
// 	else if (operation == DETACH)
// 		return (process_thread_handler(pthread_detach(*thread), operation));
// 	else
// 		return (THREAD_OPERATION_ERR_MSG);
// 	return (NULL);
// }
