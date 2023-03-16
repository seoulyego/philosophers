/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:52:39 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/16 18:33:44 by yeongo           ###   ########.fr       */
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
	while (waiting_time <= target_time)
	{
		gettimeofday(&progress_time, NULL);
		waiting_time = get_timestamp(progress_time, started_time);
		usleep(10);
	}
}

int	philo_think(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	print_philo(philo, THINKING);
	return (1);
}

static int	eat_spaghetti(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	philo->eat_count++;
	philo->last_eat_time = philo->cur_time;
	if (print_philo(philo, EATING) == 0)
		return (0);
	spend_time(philo, philo->shared->info[TIME_TO_EAT]);
	return (1);
}

int	philo_eating(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	pthread_mutex_lock(&philo->shared->m_forks[philo->r_fork]);
	pthread_mutex_lock(&philo->shared->m_forks[philo->l_fork]);
	if (take_forks(philo) == 0)
		return (0);
	if (eat_spaghetti(philo) == 0)
		return (0);
	if (get_down_forks(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
	return (1);
}

int	philo_sleep(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	if (print_philo(philo, SLEEPING) == 0)
		return (0);
	spend_time(philo, philo->shared->info[TIME_TO_SLEEP]);
	return (1);
}
