/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:16:52 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/02 16:43:25 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_data(t_data *data)
{
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->fork)
	{
		sem_close(data->fork);
		sem_unlink("/fork");
		data->fork = NULL;
	}
	if (data->print_sem)
	{
		sem_close(data->print_sem);
		sem_unlink("/print_sem");
		data->print_sem = NULL;
	}
	if (data->death)
	{
		sem_close(data->death);
		sem_unlink("/death");
		data->death = NULL;
	}
	if (data->death_lock)
	{
		sem_close(data->death_lock);
		sem_unlink("/death_lock");
		data->death_lock = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parse_args(&data, argv);
		init_data(&data);
		start_simulation(&data);
		free_data(&data);
	}
	else
	{
		error("Error: Invalid number of arguments");
	}
	return (0);
}
