/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simualtion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:53 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/27 19:49:18 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->fork[philo->right_fork]);
	print_status(data, philo->id, "has taken a fork");
	if (data->number_of_philo == 1)
	{
		_usleep(data->time_to_die);
		print_status(data, philo->id, "died");
		pthread_mutex_unlock(&data->fork[philo->right_fork]);
		set_bool(&data->mutex, &data->simulation_end, true);
		return ;
	}
	pthread_mutex_lock(&data->fork[philo->left_fork]);
	print_status(data, philo->id, "has taken a fork");
	set_long(&data->mutex, &philo->last_meal, get_time());
	print_status(data, philo->id, "is eating");
	_usleep(data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->fork[philo->left_fork]);
	pthread_mutex_unlock(&data->fork[philo->right_fork]);
}

void	sleeping(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is sleeping");
	_usleep(data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		sleeping(philo, data);
	while (!get_bool(&data->mutex, &data->simulation_end))
	{
		print_status(data, philo->id, "is thinking");
		eating(philo, data);
		sleeping(philo, data);
	}
	return (NULL);
}

void	monitor(t_data *data)
{
	int	i;
	int	full_philosophers;

	while (!get_bool(&data->mutex, &data->simulation_end))
	{
		full_philosophers = 0;
		i = -1;
		while (++i < data->number_of_philo)
		{
			if (get_time() - get_long(&data->mutex,
					&data->philo[i].last_meal) >= data->time_to_die)
			{
				print_status(data, data->philo[i].id, "died");
				return ;
			}
			if (data->meals_limit != -1 && get_long(&data->mutex,
					&data->philo[i].meals_eaten) >= data->meals_limit)
				full_philosophers++;
		}
		if (full_philosophers == data->number_of_philo)
			set_bool(&data->mutex, &data->simulation_end, true);
		usleep(100);
	}
}

int	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].last_meal = data->start_time;
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]) != 0)
			return (error("Error: pthread_create failed"));
		i++;
	}
	monitor(data);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (error("Error: pthread_join failed"));
		i++;
	}
	return (0);
}
