/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/29 14:55:58 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	bool			is_philo_full;
	int				last_time_eat;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_eat_frequency;
	t_philo			*philo;
	pthread_mutex_t	*fork;
}					t_data;

void				parse_args(t_data *data, char **argv);

#endif