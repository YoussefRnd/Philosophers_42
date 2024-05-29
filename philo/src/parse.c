/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:36:00 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/27 16:42:34 by yboumlak         ###   ########.fr       */
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
		error("Error: negative number");
	while (!is_digit(*str))
		error("Error: invalid number");
	number = str;
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = is_valid(str);
	while (is_digit(*str))
		num = num * 10 + (*str++ - '0');
	if (num > INT_MAX)
		error("Error: number is too big, INT_MAX is the limit");
	return (num);
}

void	parse_args(t_data *data, char **argv)
{
	data->number_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		error("Error: time must be at least 60ms");
	if (argv[5])
		data->philo_eat_frequency = ft_atol(argv[5]);
	else
		data->philo_eat_frequency = -1;
}
