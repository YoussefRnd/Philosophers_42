/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simualtion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:53 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/01 20:36:10 by yboumlak         ###   ########.fr       */
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

	pthread_mutex_lock(&data->print_mutex);
	if (!data->simulation_end)
	{
		timestamp = get_time() - data->start_time;
		printf("%ld %d %s\n", timestamp, id, status);
	}
	pthread_mutex_unlock(&data->print_mutex);
}

void	_usleep(int ms)
{
	long	start_time;
	long	end_time;

	start_time = get_time();
	end_time = start_time + ms;
	while (get_time() < end_time)
		usleep(85);
}

void	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (get_bool(&data->mutex, &data->simulation_end))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_status(data, philo->id, "has taken a fork");
	print_status(data, philo->id, "is eating");
	set_value(&data->mutex, &philo->last_meal, get_time());
	_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->meals_eaten++;
}

void	sleeping(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is sleeping");
	_usleep(data->time_to_sleep);
}

void	thinking(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!get_bool(&data->mutex, &data->simulation_end))
	{
		thinking(philo, data);
		eating(philo, data);
		if (data->philo_eat_frequency != -1
			&& philo->meals_eaten >= data->philo_eat_frequency)
		{
			set_bool(&data->mutex, &philo->is_philo_full, true);
			break ;
		}
		sleeping(philo, data);
	}
	return (NULL);
}

void	monitor(t_data *data)
{
	int		i;
	long	time;
	int		full_philosophers;

	while (!get_bool(&data->mutex, &data->simulation_end))
	{
		full_philosophers = 0;
		for (i = 0; i < data->number_of_philo; i++)
		{
			time = get_time();
			if (time - get_value(&data->mutex,
					&data->philo[i].last_meal) >= data->time_to_die)
			{
				print_status(data, data->philo[i].id, "died");
				set_bool(&data->mutex, &data->simulation_end, true);
				return ;
			}
			if (get_bool(&data->mutex, &data->philo[i].is_philo_full))
				full_philosophers++;
		}
		if (full_philosophers == data->number_of_philo)
		{
			set_bool(&data->mutex, &data->simulation_end, true);
			return ;
		}
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time();
	data->simulation_end = false;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	for (i = 0; i < data->number_of_philo; i++)
	{
		data->philo[i].last_meal = data->start_time;
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
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->mutex);
}
