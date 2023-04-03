/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_down_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:23:15 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 14:20:10 by yeongo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"

static int	get_down_l_fork(t_philosopher *philo, t_shared_data *shared)
{
	shared->forks[philo->l_fork] = AVAILABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->l_fork]);
	return (SUCCESS);
}

static int	get_down_r_fork(t_philosopher *philo, t_shared_data *shared)
{
	shared->forks[philo->r_fork] = AVAILABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->r_fork]);
	return (SUCCESS);
}

int	get_down_forks(t_philosopher *philo)
{
	get_down_l_fork(philo, philo->shared)
		|| get_down_r_fork(philo, philo->shared);
	return (SUCCESS);
}
