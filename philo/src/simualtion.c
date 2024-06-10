/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simualtion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:53 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/09 17:41:06 by yboumlak         ###   ########.fr       */
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
	pthread_mutex_unlock(&data->fork[philo->right_fork]);
	pthread_mutex_unlock(&data->fork[philo->left_fork]);
	set_long(&data->mutex, &philo->meals_eaten, get_long(&data->mutex,
			&philo->meals_eaten) + 1);
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
	if (philo->id % 2 == 0)
		sleeping(philo, data);
	while (!get_bool(&data->mutex, &data->simulation_end))
	{
		thinking(philo, data);
		eating(philo, data);
		sleeping(philo, data);
		if (data->meals_limit != -1 && get_long(&data->mutex,
				&philo->meals_eaten) >= data->meals_limit)
			break ;
	}
	return (NULL);
}

void	monitor(t_data *data)
{
	int		i;
	long	time;
	int		full_philosophers;
	long	last_meal_time;

	while (!get_bool(&data->mutex, &data->simulation_end))
	{
		full_philosophers = 0;
		i = 0;
		while (i < data->number_of_philo)
		{
			time = get_time();
			last_meal_time = get_long(&data->mutex, &data->philo[i].last_meal);
			if (time - last_meal_time >= data->time_to_die)
			{
				print_status(data, data->philo[i].id, "died");
				set_bool(&data->mutex, &data->simulation_end, true);
				return ;
			}
			if (data->meals_limit != -1 && get_long(&data->mutex,
					&data->philo[i].meals_eaten) >= data->meals_limit)
				full_philosophers++;
			i++;
		}
		if (full_philosophers == data->number_of_philo)
		{
			set_bool(&data->mutex, &data->simulation_end, true);
			return ;
		}
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
