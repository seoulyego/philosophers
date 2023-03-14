/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:52:39 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/14 20:20:50 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "monitor.h"
#include "message.h"
#include <unistd.h>

static void	spend_time(t_philosopher *philo, int index_info)
{
	const int		spend_time = philo->shared->info[index_info];
	const t_time	start_time = philo->cur_time;
	int				passed_time;

	gettimeofday(&philo->cur_time, NULL);
	passed_time = get_timestamp(philo->cur_time, start_time);
	while (passed_time < spend_time)
	{
		usleep(spend_time * 100);
		gettimeofday(&philo->cur_time, NULL);
		passed_time = get_timestamp(philo->cur_time, start_time);
	}
}

int	the_thinker(t_philosopher *philo)
{
	if (monitor_philo(philo) == TRUE)
		return (0);
	gettimeofday(&philo->cur_time, NULL);
	print_philo(philo, THINKING);
	usleep(100);
	return (1);
}

static int	eat_spaghetti(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if (print_philo(philo, EATING) == TRUE)
		return (0);
	philo->last_eat_time = philo->cur_time;
	spend_time(philo, TIME_TO_EAT);
	philo->eat_count++;
	return (1);
}

int	eating(t_philosopher *philo)
{
	if (monitor_philo(philo) == TRUE)
		return (0);
	if (take_forks(philo) == 0)
		return (0);
	if (eat_spaghetti(philo) == 0)
		return (0);
	if (get_down_forks(philo) == 0)
		return (0);
	return (1);
}

int	dreams_come_true(t_philosopher *philo)
{
	if (monitor_philo(philo) == TRUE)
		return (0);
	gettimeofday(&philo->cur_time, NULL);
	print_philo(philo, SLEEPING);
	spend_time(philo, TIME_TO_SLEEP);
	return (1);
}
