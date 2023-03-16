/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:49 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/16 13:52:15 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"

int	hungry_philo(t_philosopher *philo)
{
	int	starving_time;

	starving_time = get_timestamp(philo->cur_time, philo->last_eat_time);
	if (starving_time >= philo->shared->info[TIME_TO_DIE])
	{
		print_philo(philo, DIED);
		return (TRUE);
	}
	return (FALSE);
}

int	finish_philo(t_philosopher *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->shared->m_someone_die);
	pthread_mutex_lock(&philo->shared->m_all_eat);
	ret = (philo->shared->someone_die == 1
			|| philo->shared->all_eat == philo->shared->info[PHILOS]);
	pthread_mutex_unlock(&philo->shared->m_all_eat);
	pthread_mutex_unlock(&philo->shared->m_someone_die);
	return (ret);
}

int	monitor_philo(t_philosopher *philo)
{
	return (hungry_philo(philo) == TRUE
		|| finish_philo(philo) == TRUE);
}

void	check_all_eat(t_philosopher *philo)
{
	if (philo->eat_count == philo->shared->info[MUST_EAT])
	{
		pthread_mutex_lock(&philo->shared->m_all_eat);
		philo->shared->all_eat++;
		pthread_mutex_unlock(&philo->shared->m_all_eat);
	}
}

void	set_someone_died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared->m_someone_die);
	philo->shared->someone_die = 1;
	pthread_mutex_unlock(&philo->shared->m_someone_die);
}
