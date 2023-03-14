/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:52:39 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/14 23:01:14 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "monitor.h"
#include "message.h"
#include <unistd.h>

static void	spend_time(t_philosopher *philo, int index_info)
{
	const int		mealtime = philo->shared->info[index_info];
	const t_time	started_eating = philo->cur_time;
	t_time			while_eating;
	int				passed_time;

	gettimeofday(&while_eating, NULL);
	passed_time = get_timestamp(while_eating, started_eating);
	while (passed_time < mealtime)
	{
		usleep(mealtime * 100);
		gettimeofday(&while_eating, NULL);
		passed_time = get_timestamp(while_eating, started_eating);
	}
}

int	the_thinker(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	print_philo(philo, THINKING);
	usleep(100);
	return (1);
}

static int	eat_spaghetti(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	print_philo(philo, EATING);
	spend_time(philo, TIME_TO_EAT);
	philo->last_eat_time = philo->cur_time;
	philo->eat_count++;
	return (1);
}

int	eating(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	if (take_forks(philo))
	{
		if (eat_spaghetti(philo) == 0)
			return (0);
	}
	else
		return (0);
	if (get_down_forks(philo) == 0)
		return (0);
	return (1);
}

int	dreams_come_true(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (monitor_philo(philo) == TRUE)
		return (0);
	print_philo(philo, SLEEPING);
	spend_time(philo, TIME_TO_SLEEP);
	return (1);
}
