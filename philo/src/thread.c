/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:31 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/08 06:41:10 by yeongo           ###   ########.fr       */
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
		if (pthread_create(&philosopher[index].thread, NULL, \
			philo_routine, &philosopher[index]) > 0)
		{
			print_error_message("Fail to create thread");
			return (FAIL);
		}
		index++;
	}
	return (SUCCESS);
}

void	monitor_thread(
		t_philosopher *philosopher, t_shared_data *shared, int philos)
{
	int	index;
	int	id;
	int	result;

	id = -1;
	index = 0;
	result = FALSE;
	usleep(shared->info[TIME_TO_DIE] * 500);
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

int	join_thread(t_philosopher *philosopher, int philos)
{
	int	index;

	index = 0;
	while (index < philos)
	{
		if (pthread_join(philosopher[index].thread, NULL) > 0)
		{
			print_error_message("Fail to join thread");
			return (FAIL);
		}
		index++;
	}
	return (SUCCESS);
}

int	create_thread(t_philosopher *philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];

	set_f_routine(shared->f_routine);
	gettimeofday(&shared->start_time, NULL);
	if (run_thread(philosopher, philos) == FAIL)
		return (FAIL);
	monitor_thread(philosopher, shared, philos);
	if (join_thread(philosopher, philos) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
