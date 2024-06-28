/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:24:28 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/28 19:50:24 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return (error("Error: malloc failed"));
	data->simulation_end = false;
	i = 0;
	sem_unlink("/fork");
	data->fork = sem_open("/fork", O_CREAT, 0644, data->number_of_philo);
	while (i < data->number_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		i++;
	}
	sem_unlink("/print_mutex");
	data->print_mutex = sem_open("/print_mutex", O_CREAT, 0644, 1);
	sem_unlink("/mutex");
	data->mutex = sem_open("/mutex", O_CREAT, 0644, 1);
	sem_unlink("/death");
	data->death = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
	return (0);
}
