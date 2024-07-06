/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:48:49 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/06 13:59:18 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*meals_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->number_of_philo)
		sem_wait(data->philo_finished);
	sem_post(data->death);
	return (NULL);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(philo->data->last_meal_sem);
		if (get_time() - philo->last_meal >= data->time_to_die)
		{
			sem_wait(data->death_lock);
			print_status(data, philo->id, "died");
			sem_post(philo->data->last_meal_sem);
			sem_post(data->death);
			exit(0);
		}
		sem_post(philo->data->last_meal_sem);
		usleep(1000);
	}
	return (NULL);
}
