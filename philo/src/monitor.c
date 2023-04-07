/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:13:31 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/08 05:57:45 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"

int	monitor_starving(t_philosopher *philo, t_shared_data *shared)
{
	t_time	cur_time;
	int		starving_time;

	pthread_mutex_lock(&philo->m_last_eat_time);
	gettimeofday(&cur_time, NULL);
	starving_time = get_timestamp(cur_time, philo->last_eat_time);
	pthread_mutex_unlock(&philo->m_last_eat_time);
	if (starving_time >= shared->info[TIME_TO_DIE])
	{
		pthread_mutex_lock(&shared->m_end_philo);
		shared->end_philo = TRUE;
		pthread_mutex_unlock(&shared->m_end_philo);
		return (TRUE);
	}
	return (FALSE);
}

int	monitor_finish(t_shared_data *shared)
{
	pthread_mutex_lock(&shared->m_end_philo);
	if (shared->end_philo == TRUE)
	{
		pthread_mutex_unlock(&shared->m_end_philo);
		return (TRUE);
	}
	pthread_mutex_unlock(&shared->m_end_philo);
	return (FALSE);
}
