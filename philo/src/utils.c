/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:45:56 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/05 19:26:11 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (error("Error: gettimeofday failed"));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_data *data, int id, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	if (!get_bool(&data->mutex, &data->simulation_end))
	{
		timestamp = get_time() - data->start_time;
		printf("%ld %d %s\n", timestamp, id, status);
		if (!strcmp(status, "died"))
			set_bool(&data->mutex, &data->simulation_end, true);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

void	_usleep(int ms, t_data *data)
{
	long	start_time;
	long	end_time;

	start_time = get_time();
	end_time = start_time + ms;
	while (get_time() < end_time)
	{
		if (get_bool(&data->mutex, &data->simulation_end))
			break ;
		usleep(100);
	}
}
