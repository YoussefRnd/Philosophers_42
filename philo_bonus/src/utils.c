/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:45:56 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/06 14:41:26 by yboumlak         ###   ########.fr       */
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

void	create_philosopher(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error("Error: fork failed");
	else if (pid == 0)
	{
		data->philo[i].last_meal = data->start_time;
		routine(&data->philo[i], data);
		exit(0);
	}
	else
		data->philo[i].pid = pid;
	usleep(100);
}
