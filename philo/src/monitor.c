/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:49 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 10:18:51 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"

int	hungry_philo(t_philosopher *philo)
{
	long	starving_time;

	// pthread_mutex_lock(&philo->m_last_eat_time);
	starving_time = get_timestamp(philo->cur_time, philo->last_eat_time);
	// pthread_mutex_unlock(&philo->m_last_eat_time);
	if (starving_time >= philo->shared->info[TIME_TO_DIE])
		return (TRUE);
	return (FALSE);
}

int	finish_philo(t_shared_data *shared)
{
	int	ret;

	pthread_mutex_lock(&shared->m_end_philo);
	pthread_mutex_lock(&shared->m_all_eat);
	ret = (shared->end_philo == 1 || shared->all_eat == shared->info[PHILOS]);
	pthread_mutex_unlock(&shared->m_all_eat);
	pthread_mutex_unlock(&shared->m_end_philo);
	return (ret);
}

int	monitor_philo(t_shared_data *shared)
{
	int			index;
	const int	philos = shared->info[PHILOS];

	index = 0;
	while (index < philos)
	{
		// if (hungry_philo(&philosopher[index]) == TRUE
		if (finish_philo(shared) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

void	count_all_eat(t_philosopher *philo)
{
	if (philo->eat_count == philo->shared->info[MUST_EAT])
	{
		pthread_mutex_lock(&philo->shared->m_all_eat);
		philo->shared->all_eat++;
		pthread_mutex_unlock(&philo->shared->m_all_eat);
	}
}

void	set_finish_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared->m_end_philo);
	philo->shared->end_philo = 1;
	pthread_mutex_unlock(&philo->shared->m_end_philo);
}
