/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/06 14:42:47 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	sem_t				*philo_finished;
	sem_t				*last_meal_sem;
	sem_t				*start_barrier;
}						t_data;

int						parse_args(t_data *data, char **argv);

int						init_data(t_data *data);

void					start_simulation(t_data *data);
void					create_philosopher(t_data *data, int i);

void					*meals_monitor(void *arg);
void					*death_monitor(void *arg);

void					error(char *message);

long					get_time(void);

void					print_status(t_data *data, int id, char *status);

void					_usleep(int ms);

void					kill_processes(t_data *data);

#endif