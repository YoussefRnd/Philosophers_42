/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:24:28 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/06 16:17:30 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return error("Error: malloc failed");
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->fork)
		return error("Error: malloc failed");
	data->simulation_end = false;
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return error("Error: mutex init failed");
		data->philo[i].right_fork = &data->fork[(i + 1)
			% data->number_of_philo];
		data->philo[i].left_fork = &data->fork[i];
		i++;
	}
	return 0;
}
