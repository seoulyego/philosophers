/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:31 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/30 17:59:01 yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"
#include "monitor.h"
#include "routine.h"

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
	while (1)
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

	gettimeofday(&shared->start_time, NULL);
	run_thread(philosopher, philos);
	monitor_thread(philosopher, shared, philos);
	// reclaim_thread(philosopher, philos);
	return (1);
}
