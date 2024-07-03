/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/02 16:36:02 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data	t_data;
typedef struct s_philo
{
	int					id;
	pid_t				pid;
	pthread_t			thread;
	long				last_meal;
	int					meals_eaten;
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
	sem_t				*fork;
	long				start_time;
	sem_t				*death;
	sem_t				*death_lock;
	sem_t				*print_sem;
}						t_data;

int						parse_args(t_data *data, char **argv);

int						init_data(t_data *data);

void					start_simulation(t_data *data);

void					error(char *message);

long					get_time(void);

void					print_status(t_data *data, int id, char *status);

void					_usleep(int ms);

void					kill_processes(t_data *data);

#endif