/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:16:52 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/06 16:23:44 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	}
	else
	{
		return (1);
	}
	return (0);
}
