/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:06:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/27 14:52:09 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "message.h"

static int	take_right_fork(t_philosopher *philo, t_shared_data *shared)
{
	if (finish_philo(philo->shared) == TRUE)
		return (0);
	pthread_mutex_lock(&philo->shared->m_forks[philo->r_fork]);
	if (shared->forks[philo->r_fork] == AVAILABLE)
		shared->forks[philo->r_fork] = DISABLE;
	return (1);
}

static int	take_left_fork(t_philosopher *philo, t_shared_data *shared)
{
	if (finish_philo(philo->shared) == TRUE)
		return (0);
	pthread_mutex_lock(&philo->shared->m_forks[philo->l_fork]);
	if (shared->forks[philo->l_fork] == AVAILABLE)
		shared->forks[philo->l_fork] = DISABLE;
	return (1);
}

int	take_forks(t_philosopher *philo)
{
	if (finish_philo(philo->shared) == TRUE)
		return (0);
	if (take_right_fork(philo, philo->shared)
		&& take_left_fork(philo, philo->shared))
	{
		gettimeofday(&philo->cur_time, NULL);
		if (print_philo(philo, TAKE_FORK) == 0)
		{
			pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
			pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
			return (0);
		}
		return (1);
	}
	return (0);
}
