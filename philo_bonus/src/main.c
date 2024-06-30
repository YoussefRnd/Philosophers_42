/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:16:52 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/30 12:46:01 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_data(t_data *data)
{
	int	i;

	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->fork)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			sem_post(data->fork);
			i++;
		}
		sem_close(data->fork);
		data->fork = NULL;
	}
	if (data->print_sem)
	{
		sem_post(data->print_sem);
		sem_close(data->print_sem);
		data->print_sem = NULL;
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
