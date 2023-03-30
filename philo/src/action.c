/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:42:53 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/30 20:01:53 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "message.h"
#include "monitor.h"
#include <unistd.h>

int	spend_time(t_philosopher *philo, int target_time)
{
	const t_time	started_time = philo->cur_time;
	long			timestamp;

	gettimeofday(&philo->cur_time, NULL);
	timestamp = get_timestamp(philo->cur_time, started_time);
	while (timestamp <= target_time)
	{
		gettimeofday(&philo->cur_time, NULL);
		timestamp = get_timestamp(philo->cur_time, started_time);
		usleep(100);
		if (monitor_finish(philo->shared))
			return (FAIL);
	}
	return (SUCCESS);
}

int	philo_eating(t_philosopher *philo)
{
	if (take_forks(philo) && eat_philo(philo) && get_down_forks(philo) == 0)
		return (FAIL);
	return (SUCCESS);
}

int	philo_sleeping(t_philosopher *philo)
{
	if (print_routine(philo, SLEEPING) == FAIL
		|| spend_time(philo, philo->shared->info[TIME_TO_SLEEP]) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	philo_thinking(t_philosopher *philo)
{
	if (print_routine(philo, THINKING) == FAIL)
		return (FAIL);
	usleep(100);
	return (SUCCESS);
}
