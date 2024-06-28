/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:16:52 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/28 17:01:37 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->fork)
	{
		while (i < data->number_of_philo)
		{
			sem_post(data->fork);
			i++;
		}
		free(data->fork);
		data->fork = NULL;
	}
	sem_post(data->print_mutex);
	sem_post(data->mutex);
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
		// free_data(&data);
	}
	else
	{
		return (1);
	}
	return (0);
}
