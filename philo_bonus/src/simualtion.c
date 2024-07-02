/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simualtion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:53 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/02 16:34:24 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo, t_data *data)
{
	sem_wait(data->fork);
	print_status(data, philo->id, "has taken a fork");
	if (data->number_of_philo == 1)
	{
		_usleep(data->time_to_die);
		print_status(data, philo->id, "died");
		sem_post(data->fork);
		sem_post(data->death);
		exit(0);
	}
	sem_wait(data->fork);
	print_status(data, philo->id, "has taken a fork");
	philo->last_meal = get_time();
	print_status(data, philo->id, "is eating");
	_usleep(data->time_to_eat);
	philo->meals_eaten++;
	sem_post(data->fork);
	sem_post(data->fork);
}

void	sleeping(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is sleeping");
	_usleep(data->time_to_sleep);
}

void	*monitor_philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (get_time() - philo->last_meal >= data->time_to_die)
		{
			sem_wait(data->death_lock);
			print_status(data, philo->id, "died");
			sem_post(data->death);
			exit(0);
		}
		if (data->meals_limit != -1 && philo->meals_eaten >= data->meals_limit)
		{
			sem_wait(data->death_lock);
			sem_post(data->death);
			exit(0);
		}
		usleep(999);
	}
	return (NULL);
}

void	routine(t_philo *philo, t_data *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor_philosopher, philo) != 0)
		error("Error: pthread_create failed");
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
		sleeping(philo, data);
	while (1)
	{
		print_status(data, philo->id, "is thinking");
		eating(philo, data);
		sleeping(philo, data);
	}
}

void	start_simulation(t_data *data)
{
	int		i;
	pid_t	pid;

	data->start_time = get_time();
	i = -1;
	while (++i < data->number_of_philo)
	{
		pid = fork();
		data->philo[i].last_meal = data->start_time;
		if (pid < 0)
			error("Error: fork failed");
		else if (pid == 0)
		{
			routine(&data->philo[i], data);
			exit(0);
		}
		else
			data->philo[i].pid = pid;
	}
	if (waitpid(0, NULL, 0) > 0)
	{
		sem_wait(data->death);
		kill_processes(data);
	}
}
