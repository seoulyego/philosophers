/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:40:23 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/08 03:15:52 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "monitor.h"
#include "utils.h"
#include <stdio.h>

long	get_timestamp(t_time cur_time, t_time start_time)
{
	return ((cur_time.tv_sec - start_time.tv_sec) * 1000 \
	+ (cur_time.tv_usec - start_time.tv_usec) / 1000);
}

int	print_routine(t_philosopher *philo, t_shared_data *shared, int routine)
{
	int				timestamp;
	const char		*message[5] = {
		"is eating", "is sleeping", "is thinking", "has taken a fork",
		"get down a fork"
	};

	pthread_mutex_lock(&shared->m_print);
	gettimeofday(&philo->cur_time, NULL);
	timestamp = get_timestamp(philo->cur_time, shared->start_time);
	if (monitor_finish(shared) == FALSE)
		printf("%d %d %s\n", timestamp, philo->id, message[routine]);
	else
	{
		pthread_mutex_unlock(&shared->m_print);
		return (FAIL);
	}
	pthread_mutex_unlock(&shared->m_print);
	return (SUCCESS);
}

int	print_death(t_philosopher *philo, t_shared_data *shared)
{
	int	timestamp;

	gettimeofday(&philo->cur_time, NULL);
	timestamp = get_timestamp(philo->cur_time, shared->start_time);
	pthread_mutex_lock(&shared->m_print);
	printf("%d %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&shared->m_print);
	return (SUCCESS);
}

void	print_error_message(char *err_message)
{
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
