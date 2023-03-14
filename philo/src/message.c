/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:40:23 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/14 20:18:50 by yeongo           ###   ########.fr       */
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
	static const char	*philo_msg[5] =
	{"is thinking", "is eating", "is sleeping", "died", "has taken a fork"};

	pthread_mutex_lock(&philo->shared->m_print);
	timestamp = get_timestamp(philo->cur_time, philo->shared->start_time);
	if (finish_philo(philo) == FALSE)
		printf("%d %d %s\n", timestamp, philo->id, philo_msg[routine]);
	pthread_mutex_unlock(&philo->shared->m_print);
	if (routine == EATING)
		increase_eat_count(philo);
	if (routine == DIED)
	{
		check_someone_died(philo);
		return (0);
	}
	return (1);
}

void	print_error_message(char *err_message)
{
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
