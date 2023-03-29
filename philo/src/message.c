/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:40:23 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 20:52:14 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "utils.h"
#include <stdio.h>

int	print_routine(t_philosopher *philo, t_shared_data *shared, int routine)
{
	pthread_mutex_lock(&shared->m_print);
	printf("philo[%d] : hi\n", philo->id);
	pthread_mutex_unlock(&shared->m_print);
	return (1);
}

int	print_death(t_philosopher *philo, t_shared_data *shared)
{
	long	timestamp;

	timestamp = get_timestamp(philo->cur_time, shared->start_time);
	printf("%d %d is died\n", timestamp, philo->id);
	return (1);
}

void	print_error_message(char *err_message)
{
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
