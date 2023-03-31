/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:01:52 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/31 10:51:26 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "message.h"
#include "monitor.h"
#include <unistd.h>

static void	set_f_routine(int (*f_routine[F_NUM])(t_philosopher *))
{
	f_routine[EATING] = philo_eating;
	f_routine[SLEEPING] = philo_sleeping;
	f_routine[THINKING] = philo_thinking;
}

static void	init_philo_time(t_philosopher *philo, t_shared_data *shared)
{
	philo->cur_time = shared->start_time;
	philo->last_eat_time = shared->start_time;
}

void	*philo_routine(void *philosopher)
{
	t_philosopher	*philo;
	t_shared_data	*shared;
	static int		(*f_routine[F_NUM])(t_philosopher *);

	philo = philosopher;
	shared = philo->shared;
	init_philo_time(philo, philo->shared);
	if (philo->id == 1)
		set_f_routine(f_routine);
	if (philo->id % 2 == 0)
		usleep(100);
	else if (philo->id % 2 == 1
		&& philo->id == shared->info[PHILOS])
		usleep(100);
	while (monitor_finish(shared) == FALSE)
	{
		if (f_routine[philo->routine](philo) == FAIL)
			break ;
		philo->routine = (philo->routine + 1) % F_NUM;
	}
	return (NULL);
}
