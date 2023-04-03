/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:01:52 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 19:18:37 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"
#include "monitor.h"
#include <unistd.h>

static void	init_philo_time(t_philosopher *philo, t_shared_data *shared)
{
	philo->cur_time = shared->start_time;
	philo->last_eat_time = shared->start_time;
}

void	*philo_routine(void *philosopher)
{
	t_philosopher	*philo;
	t_shared_data	*shared;

	philo = philosopher;
	shared = philo->shared;
	usleep(500);
	init_philo_time(philo, philo->shared);
	if (philo->id % 2 == 0)
		usleep(shared->info[TIME_TO_EAT] * 500);
	while (monitor_finish(shared) == FALSE)
	{
		if (shared->f_routine[philo->routine](philo) == FAIL)
			break ;
		philo->routine = (philo->routine + 1) % F_NUM;
	}
	return (NULL);
}
