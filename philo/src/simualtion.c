/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simualtion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:53 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/30 14:41:53 by yboumlak         ###   ########.fr       */
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

	timestamp = get_time() - data->start_time;
	printf("%ld %d %s\n", timestamp, id, status);
}

void	*routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (true)
	{
		pthread_mutex_lock(data->philo->left_fork);
		print_status(data, data->philo->id, "has taken a fork");
		pthread_mutex_lock(data->philo->right_fork);
		print_status(data, data->philo->id, "has taken a fork");
		print_status(data, data->philo->id, "is eating");
		data->philo->last_meal = get_time();
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(data->philo->right_fork);
		pthread_mutex_unlock(data->philo->left_fork);
		data->philo->meals_eaten++;
		if (data->philo_eat_frequency != -1
			&& data->philo->meals_eaten >= data->philo_eat_frequency)
		{
			data->philo->is_philo_full = true;
			break ;
		}
		print_status(data, data->philo->id, "is sleeping");
		usleep(data->time_to_sleep * 1000);
		print_status(data, data->philo->id, "is thinking");
	}
	return (NULL);
}

void	monitor(t_data *data)
{
	int		i;
	long	time;

	while (true)
	{
		for (i = 0; i < data->number_of_philo; i++)
		{
			time = get_time();
			if (time - data->philo[i].last_meal > data->time_to_die)
			{
				print_status(data, data->philo[i].id, "died");
				return ;
			}
			if (data->philo[i].is_philo_full)
				return ;
		}
		usleep(1000);
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time();
	for (i = 0; i < data->number_of_philo; i++)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]) != 0)
			error("Error: pthread_create failed");
	}
	monitor(data);
	for (i = 0; i < data->number_of_philo; i++)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			error("Error: pthread_join failed");
	}
}
