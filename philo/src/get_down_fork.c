/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_down_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:23:15 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 17:41:25 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "message.h"

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

int	get_down_forks(t_philosopher *philo, t_shared_data *shared)
{
	if (get_down_l_fork(philo, shared) == FAIL
		|| get_down_r_fork(philo, shared) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
