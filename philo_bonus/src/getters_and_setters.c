// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   getters_and_setters.c                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/06/10 13:07:29 by yboumlak          #+#    #+#             */
// /*   Updated: 2024/06/28 16:20:02 by yboumlak         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../inc/philo.h"

// void	set_long(sem_t *mutex, long *arg, long value)
// {
// 	sem_wait(mutex);
// 	*arg = value;
// 	sem_post(mutex);
// }

// long	get_long(sem_t *mutex, long *arg)
// {
// 	long	value;

// 	sem_wait(mutex);
// 	value = *arg;
// 	sem_post(mutex);
// 	return (value);
// }

// void	set_bool(sem_t *mutex, bool *arg, bool value)
// {
// 	sem_wait(mutex);
// 	*arg = value;
// 	sem_post(mutex);
// }

// bool	get_bool(sem_t *mutex, bool *arg)
// {
// 	bool	value;
// 	sem_wait(mutex);
// 	value = *arg;
// 	sem_post(mutex);
// 	return (value);
// }