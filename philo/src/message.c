/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:40:23 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 10:07:54 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "utils.h"
#include <stdio.h>

int	get_timestamp(t_time cur_time, t_time start_time)
{
	return ((cur_time.tv_sec - start_time.tv_sec) * 1000
		+ (cur_time.tv_usec - start_time.tv_usec) / 1000);
}

int	print_philo(t_philosopher *philo, int routine)
{
	int					timestamp;
	static const char	*message[5]
		= {"is eating", "is sleeping", "is thinking", \
			"died", "has taken a fork"};

	if (finish_philo(philo->shared) == TRUE)
		return (0);
	pthread_mutex_lock(&philo->shared->m_print);
	gettimeofday(&philo->cur_time, NULL);
	pthread_mutex_lock(&philo->shared->m_start_time);
	timestamp = get_timestamp(philo->cur_time, philo->shared->start_time);
	pthread_mutex_unlock(&philo->shared->m_start_time);
	if (finish_philo(philo->shared) == FALSE)
		printf("%d %d %s\n", timestamp, philo->id, message[routine]);
	pthread_mutex_unlock(&philo->shared->m_print);
	if (routine == DIED)
	{
		set_finish_philo(philo);
		return (0);
	}
	else if (routine == EATING && philo->shared->info[IS_LIMIT_EAT])
	{
		count_all_eat(philo);
		return (finish_philo(philo->shared) != TRUE);
	}
	return (1);
}

void	print_error_message(char *err_message)
{
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
