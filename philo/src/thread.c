/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:31 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 18:09:40 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "message.h"
#include "monitor.h"
#include "routine.h"
#include <unistd.h>

static void	set_f_routine(int (*f_routine[F_NUM])(t_philosopher *))
{
	f_routine[EATING] = philo_eating;
	f_routine[SLEEPING] = philo_sleeping;
	f_routine[THINKING] = philo_thinking;
}

int	run_thread(t_philosopher *philosopher, int philos)
{
	int	index;

	index = 0;
	while (index < philos)
	{
		pthread_create(&philosopher[index].thread, NULL, \
			philo_routine, &philosopher[index]);
		pthread_detach(philosopher[index].thread);
		index++;
	}
	return (1);
}

void	monitor_thread(t_philosopher *philosopher, \
	t_shared_data *shared, int philos)
{
	int	index;
	int	id;
	int	result;

	id = -1;
	index = 0;
	result = FALSE;
	// usleep(shared->info[TIME_TO_DIE] * 500);
	while (result == FALSE)
	{
		result = monitor_starving(&philosopher[index], shared);
		if (result == TRUE)
		{
			id = index;
			break ;
		}
		result = monitor_finish(shared);
		index = (index + 1) % philos;
		usleep(100);
	}
	if (id != -1)
		print_death(&philosopher[id], shared);
}

int	reclaim_thread(t_philosopher *philosopher, int philos)
{
	int	index;

	index = 0;
	while (index < philos)
	{
		pthread_join(philosopher[index].thread, NULL);
		index++;
	}
	return (1);
}

int	create_thread(t_philosopher *philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];

	set_f_routine(shared->f_routine);
	gettimeofday(&shared->start_time, NULL);
	run_thread(philosopher, philos);
	monitor_thread(philosopher, shared, philos);
	// reclaim_thread(philosopher, philos);
	return (1);
}
