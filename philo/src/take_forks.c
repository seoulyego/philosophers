/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:06:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 21:37:27 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"

static int	take_right_fork(t_philosopher *philo, t_shared_data *shared)
{
	pthread_mutex_lock(&shared->m_forks[philo->r_fork]);
	if (shared->forks[philo->r_fork] == AVAILABLE)
		shared->forks[philo->r_fork] = DISABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->r_fork]);
	return (1);
}

static int	take_left_fork(t_philosopher *philo, t_shared_data *shared)
{
	pthread_mutex_lock(&shared->m_forks[philo->l_fork]);
	if (shared->forks[philo->l_fork] == AVAILABLE)
		shared->forks[philo->l_fork] = DISABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->l_fork]);
	return (1);
}

int	take_forks(t_philosopher *philo)
{
	if (take_right_fork(philo, philo->shared) == 0)
		return (0);
	if (take_left_fork(philo, philo->shared) == 0)
		return (0);
	return (1);
}
