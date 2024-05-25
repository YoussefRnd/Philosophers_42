/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/25 13:43:34 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		philo;
	t_fork			*right_fork;
	t_fork			*left_fork;
	bool			is_philo_full;
}					t_philo;

typedef struct s_data
{	
	long			number_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philo_eat_frequency;
	t_philo			*philo;
	t_fork			*fork;
}					t_data;

void				parse_args(t_data *data, char **argv);