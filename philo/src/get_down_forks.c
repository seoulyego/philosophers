/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_down_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:05:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 21:37:27 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"

static int	get_down_right_fork(t_philosopher *philo, t_shared_data *shared)
{
	pthread_mutex_lock(&shared->m_forks[philo->r_fork]);
	if (shared->forks[philo->r_fork] == DISABLE)
		shared->forks[philo->r_fork] = AVAILABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->r_fork]);
	return (1);
}

static int	get_down_left_fork(t_philosopher *philo, t_shared_data *shared)
{
	pthread_mutex_lock(&shared->m_forks[philo->l_fork]);
	if (shared->forks[philo->l_fork] == DISABLE)
		shared->forks[philo->l_fork] = AVAILABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->l_fork]);
	return (1);
}

int	get_down_forks(t_philosopher *philo)
{
	if (get_down_right_fork(philo, philo->shared) == 0)
		return (0);
	if (get_down_left_fork(philo, philo->shared) == 0)
		return (0);
	return (1);
}
