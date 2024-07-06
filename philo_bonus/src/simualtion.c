/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simualtion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:53 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/06 14:40:37 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo, t_data *data)
{
	sem_wait(data->fork);
	print_status(data, philo->id, "has taken a fork");
	sem_wait(data->fork);
	print_status(data, philo->id, "has taken a fork");
	sem_wait(data->last_meal_sem);
	philo->last_meal = get_time();
	print_status(data, philo->id, "is eating");
	sem_post(data->last_meal_sem);
	_usleep(data->time_to_eat);
	philo->meals_eaten++;
	if (data->meals_limit != -1 && philo->meals_eaten == data->meals_limit)
		sem_post(data->philo_finished);
	sem_post(data->fork);
	sem_post(data->fork);
}

void	sleeping(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is sleeping");
	_usleep(data->time_to_sleep);
}

void	routine(t_philo *philo, t_data *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &death_monitor, philo) != 0)
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
	int			i;
	pthread_t	monitor_all_thread;

	if (pthread_create(&monitor_all_thread, NULL, &meals_monitor, data) != 0)
		error("Error: pthread_create failed");
	pthread_detach(monitor_all_thread);
	data->start_time = get_time();
	i = -1;
	while (++i < data->number_of_philo)
		create_philosopher(data, i);
	sem_wait(data->death);
	kill_processes(data);
}
