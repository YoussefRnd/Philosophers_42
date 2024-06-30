/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:24:28 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/30 12:38:50 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		error("Error: malloc failed");
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
	sem_unlink("/print_sem");
	data->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	sem_unlink("/death");
	data->death = sem_open("/death", O_CREAT, 0644, 0);
	return (0);
}
