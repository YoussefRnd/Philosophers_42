/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:36:00 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/09 17:10:17 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static char	*is_valid(char *str)
{
	char	*number;

	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		error("Error: negative number");
		return (NULL);
	}
	number = str;
	while (is_digit(*str))
		str++;
	if (*str)
	{
		error("Error: invalid number");
		return (NULL);
	}
	return (number);
}

static long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = is_valid(str);
	if (str == NULL)
		return (-1);
	while (is_digit(*str))
		num = num * 10 + (*str++ - '0');
	if (num > INT_MAX)
		return (error("Error: number is too big, INT_MAX is the limit"));
	return (num);
}

int	parse_args(t_data *data, char **argv)
{
	data->number_of_philo = ft_atol(argv[1]);
	if (data->number_of_philo == -1)
		return (-1);
	data->time_to_die = ft_atol(argv[2]);
	if (data->time_to_die == -1)
		return (-1);
	data->time_to_eat = ft_atol(argv[3]);
	if (data->time_to_eat == -1)
		return (-1);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_sleep == -1)
		return (-1);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (error("Error: time must be at least 60ms"));
	if (argv[5])
	{
		data->meals_limit = ft_atol(argv[5]);
		if (data->meals_limit == -1)
			return (-1);
	}
	else
		data->meals_limit = -1;
	return (0);
}
