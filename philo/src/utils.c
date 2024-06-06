/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:45:56 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/06 16:12:39 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_long(pthread_mutex_t *mutex, long *arg, long value)
{
	pthread_mutex_lock(mutex);
	*arg = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(pthread_mutex_t *mutex, long *arg)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *arg;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_bool(pthread_mutex_t *mutex, bool *arg, bool value)
{
	pthread_mutex_lock(mutex);
	*arg = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *arg)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *arg;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_int(pthread_mutex_t *mutex, int *arg, int value)
{
	pthread_mutex_lock(mutex);
	*arg = value;
	pthread_mutex_unlock(mutex);
}
