/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:45:56 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/02 16:35:39 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error("Error: gettimeofday failed");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_data *data, int id, char *status)
{
	long	timestamp;

	sem_wait(data->print_sem);
	timestamp = get_time() - data->start_time;
	printf("%ld %d %s\n", timestamp, id, status);
	if (strcmp(status, "died") != 0)
		sem_post(data->print_sem);
}

void	_usleep(int ms)
{
	long	start_time;
	long	end_time;

	start_time = get_time();
	end_time = start_time + ms;
	while (get_time() < end_time)
		usleep(100);
}

void	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		kill(data->philo[i].pid, SIGTERM);
		i++;
	}
}
