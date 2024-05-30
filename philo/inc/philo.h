/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/30 13:54:03 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	bool			is_philo_full;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_eat_frequency;
	long			start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork;
}					t_data;

void				parse_args(t_data *data, char **argv);

void				error(char *message);

void				init_data(t_data *data);

void				start_simulation(t_data *data);

#endif