/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simualtion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:53 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/29 14:54:37 by yboumlak         ###   ########.fr       */
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

void	*monitor(t_philo *philo)
{
	while (true)
	{
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].philo, NULL, &monitor,
				&data->philo[i]) != 0)
			error("Error: pthread_create failed");
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(data->philo[i].philo, NULL) != 0)
			error("Error: pthread_join failed");
		i++;
	}
}
