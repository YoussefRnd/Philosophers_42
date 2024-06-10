/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/06/10 17:04:29 by yboumlak         ###   ########.fr       */
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
	int					id;
	pthread_t			thread;
	int					right_fork;
	int					left_fork;
	long				last_meal;
	long				meals_eaten;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_limit;
	t_philo				*philo;
	pthread_mutex_t		*fork;
	long				start_time;
	bool				simulation_end;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		mutex;
}						t_data;

int						parse_args(t_data *data, char **argv);

int						init_data(t_data *data);

int						start_simulation(t_data *data);

int						error(char *message);

void					set_long(pthread_mutex_t *mutex, long *arg, long value);
void					set_bool(pthread_mutex_t *mutex, bool *arg, bool value);

long					get_long(pthread_mutex_t *mutex, long *arg);
bool					get_bool(pthread_mutex_t *mutex, bool *arg);

long					get_time(void);

void					print_status(t_data *data, int id, char *status);

void					_usleep(int ms);

#endif