/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:16:52 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/08 14:10:18 by yboumlak         ###   ########.fr       */
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
		for (i = 0; i < data->number_of_philo; i++)
		{
			pthread_mutex_destroy(&data->fork[i]);
		}
		free(data->fork);
		data->fork = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->mutex);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&data, argv) == -1)
			return (1);
		if (init_data(&data) == -1)
			return (1);
		if (start_simulation(&data) == -1)
			return (1);
		free_data(&data);
	}
	else
	{
		return (1);
	}
	return (0);
}
