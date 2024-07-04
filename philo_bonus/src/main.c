/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:16:52 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/04 15:30:45 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_data(t_data *data)
{
	free(data->philo);
	sem_close(data->fork);
	sem_unlink("/fork");
	sem_close(data->print_sem);
	sem_unlink("/print_sem");
	sem_close(data->death);
	sem_unlink("/death");
	sem_close(data->death_lock);
	sem_unlink("/death_lock");
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
		return (1);
	}
	return (0);
}
