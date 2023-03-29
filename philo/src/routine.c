/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:52:39 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 10:15:13 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "monitor.h"
#include "message.h"
#include <unistd.h>

static void	spend_time(t_philosopher *philo, int target_time)
{
	const t_time	started_time = philo->cur_time;
	int				waiting_time;

	gettimeofday(&philo->cur_time, NULL);
	waiting_time = get_timestamp(philo->cur_time, started_time);
	while (waiting_time <= target_time)
	{
		gettimeofday(&philo->cur_time, NULL);
		waiting_time = get_timestamp(philo->cur_time, started_time);
		usleep(500);
		if (hungry_philo(philo) == TRUE)
		{
			print_philo(philo, DIED);
			return ;
		}
	}
}

int	philo_think(t_philosopher *philo)
{
	if (finish_philo(philo->shared) == TRUE)
		return (0);
	print_philo(philo, THINKING);
	return (1);
}

static int	eat_spaghetti(t_philosopher *philo)
{
	if (finish_philo(philo->shared) == TRUE)
	{
		pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
		return (0);
	}
	philo->eat_count++;
	if (print_philo(philo, EATING) == 0)
	{
		pthread_mutex_unlock(&philo->shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->shared->m_forks[philo->r_fork]);
		return (0);
	}
	// pthread_mutex_lock(&philo->m_last_eat_time);
	philo->last_eat_time = philo->cur_time;
	// pthread_mutex_unlock(&philo->m_last_eat_time);
	spend_time(philo, philo->shared->info[TIME_TO_EAT]);
	return (1);
}

int	philo_eating(t_philosopher *philo)
{
	if (finish_philo(philo->shared) == TRUE)
		return (0);
	if (take_forks(philo) && eat_spaghetti(philo) && get_down_forks(philo) == 0)
		return (0);
	return (1);
}

int	philo_sleep(t_philosopher *philo)
{
	if (finish_philo(philo->shared) == TRUE)
		return (0);
	if (print_philo(philo, SLEEPING) == 0)
		return (0);
	spend_time(philo, philo->shared->info[TIME_TO_SLEEP]);
	return (1);
}
