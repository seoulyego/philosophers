/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:52:39 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/15 17:50:49 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "monitor.h"
#include "message.h"
#include <unistd.h>

static void	spend_time(t_philosopher *philo, int target_time)
{
	const t_time	started_time = philo->cur_time;
	t_time			progress_time;
	int				waiting_time;

	waiting_time = 0;
	while (waiting_time < target_time)
	{
		gettimeofday(&progress_time, NULL);
		waiting_time = get_timestamp(progress_time, started_time);
		usleep(100);
	}
}

int	the_thinker(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	print_philo(philo, THINKING);
	spend_time(philo, philo->shared->info[TIME_TO_SLEEP]);
	return (1);
}

static int	eat_spaghetti(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	print_philo(philo, EATING);
	spend_time(philo, philo->shared->info[TIME_TO_EAT]);
	philo->last_eat_time = philo->cur_time;
	philo->eat_count++;
	return (1);
}

int	eating(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	pthread_mutex_lock(&philo->shared->m_forks[philo->r_fork]);
	pthread_mutex_lock(&philo->shared->m_forks[philo->l_fork]);
	take_forks(philo);
	eat_spaghetti(philo);
	get_down_forks(philo);
	pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
	return (1);
}

int	dreams_come_true(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	print_philo(philo, SLEEPING);
	spend_time(philo, philo->shared->info[TIME_TO_SLEEP]);
	return (1);
}
