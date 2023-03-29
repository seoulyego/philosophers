/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_down_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:05:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 10:12:30 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

static int	get_down_left_fork(t_philosopher *philo, t_shared_data *shared)
{
	if (finish_philo(philo->shared) == TRUE)
	{
		pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
		return (0);
	}
	if (shared->forks[philo->l_fork] == DISABLE)
	{
		shared->forks[philo->l_fork] = AVAILABLE;
		pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
		return (1);
	}
	return (0);
}

static int	get_down_right_fork(t_philosopher *philo, t_shared_data *shared)
{
	if (finish_philo(philo->shared) == TRUE)
	{
		pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
		return (0);
	}
	if (shared->forks[philo->r_fork] == DISABLE)
	{
		shared->forks[philo->r_fork] = AVAILABLE;
		pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
		return (1);
	}
	return (0);
}

int	get_down_forks(t_philosopher *philo)
{
	if (finish_philo(philo->shared) == TRUE)
	{
		pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
		return (0);
	}
	if (get_down_left_fork(philo, philo->shared)
		&& get_down_right_fork(philo, philo->shared))
		return (1);
	pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
	return (0);
}
