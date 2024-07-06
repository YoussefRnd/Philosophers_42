/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:31:50 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/06 14:10:10 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

void	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		kill(data->philo[i].pid, SIGTERM);
		waitpid(data->philo[i].pid, NULL, 0);
		i++;
	}
}
