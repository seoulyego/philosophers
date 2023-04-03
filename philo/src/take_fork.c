/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:59:57 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 15:52:38 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"

static int	take_r_fork(t_philosopher *philo, t_shared_data *shared)
{
	pthread_mutex_lock(&shared->m_forks[philo->r_fork]);
	// if (shared->forks[philo->r_fork] == AVAILABLE)
	// {
	shared->forks[philo->r_fork] = DISABLE;
	if (print_routine(philo, TAKE_FORKS) == FAIL)
	{
		pthread_mutex_unlock(&shared->m_forks[philo->r_fork]);
		return (FAIL);
	}
	// }
	return (SUCCESS);
}

static int	take_l_fork(t_philosopher *philo, t_shared_data *shared)
{
	pthread_mutex_lock(&shared->m_forks[philo->l_fork]);
	// if (shared->forks[philo->l_fork] == AVAILABLE)
	// {
	shared->forks[philo->l_fork] = DISABLE;
	if (print_routine(philo, TAKE_FORKS) == FAIL)
	{
		pthread_mutex_unlock(&shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&shared->m_forks[philo->r_fork]);
		return (FAIL);
	}
	// }
	return (SUCCESS);
}

int	take_forks(t_philosopher *philo)
{
	if (take_r_fork(philo, philo->shared) == FAIL
		|| take_l_fork(philo, philo->shared) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
