/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:49 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/14 20:18:00 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"
#include "utils.h"

int	hungry_philo(t_philosopher *philo)
{
	int	starving_time;

	gettimeofday(&philo->cur_time, NULL);
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
	if (philo->shared->someone_die == 1)
		return (TRUE);
	if (philo->shared->all_eat == philo->shared->info[PHILOS])
		return (TRUE);
	return (FALSE);
}

int	monitor_philo(t_philosopher *philo)
{
	if (finish_philo(philo) == TRUE || hungry_philo(philo) == TRUE)
		return (TRUE);
	return (FALSE);
}

void	increase_eat_count(t_philosopher *philo)
{
	if (philo->eat_count == philo->shared->info[MUST_EAT])
	{
		pthread_mutex_lock(&philo->shared->m_all_eat);
		philo->shared->all_eat++;
		pthread_mutex_unlock(&philo->shared->m_all_eat);
	}
}

void	check_someone_died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared->m_someone_die);
	philo->shared->someone_die = 1;
	pthread_mutex_unlock(&philo->shared->m_someone_die);
}
