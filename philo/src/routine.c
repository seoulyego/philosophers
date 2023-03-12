/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:52:39 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 20:30:46 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "message.h"
#include <unistd.h>

static void	spend_time(t_philosopher *philo, int index_info)
{
	const int		spend_time = philo->shared->info[index_info];
	const t_time	start_time = philo->cur_time;
	t_time			cur_time;
	int				passed_time;

	gettimeofday(&cur_time, NULL);
	passed_time = get_timestamp(cur_time, start_time);
	while (passed_time < spend_time)
	{
		usleep(spend_time * 100);
		gettimeofday(&cur_time, NULL);
		passed_time = get_timestamp(cur_time, start_time);
	}
	return ;
}

int	the_thinker(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	print_philo(philo, THINKING);
	while ()
	{
		usleep(100);
	}
	return (1);
}

static int	eat_spaghetti(t_philosopher *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	print_philo(philo, EATING);
	spend_time(philo, TIME_TO_EAT);
	philo->last_eat_time = philo->cur_time;
	philo->eat_count++;
	if (philo->shared->info[MUST_EAT] != 0
		&& philo->eat_count == philo->shared->info[MUST_EAT])
	{
		pthread_mutex_lock(&philo->shared->all_eat_mutex);
		philo->shared->all_eat++;
		pthread_mutex_unlock(&philo->shared->all_eat_mutex);
	}
	return (1);
}

int	eating(t_philosopher *philo)
{
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
	gettimeofday(&philo->cur_time, NULL);
	print_philo(philo, SLEEPING);
	spend_time(philo, TIME_TO_SLEEP);
	return (1);
}
