/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_down_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:23:15 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/08 06:57:51 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "message.h"

static void	get_down_l_fork(t_philosopher *philo, t_shared_data *shared)
{
	shared->forks[philo->l_fork] = AVAILABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->l_fork]);
}

static void	get_down_r_fork(t_philosopher *philo, t_shared_data *shared)
{
	shared->forks[philo->r_fork] = AVAILABLE;
	pthread_mutex_unlock(&shared->m_forks[philo->r_fork]);
}

void	get_down_forks(t_philosopher *philo, t_shared_data *shared)
{
	get_down_l_fork(philo, shared);
	get_down_r_fork(philo, shared);
}
