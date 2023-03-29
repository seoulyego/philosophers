/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guest <Guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:31 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 23:22:09 by Guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"
#include "routine.h"

int	run_thread(t_philosopher *philosopher, int philos)
{
	int	index;

	index = 0;
	while (index < philos)
	{
		pthread_create(&philosopher[index].thread, NULL, \
			philo_routine, &philosopher[index]);
		index++;
	}
	return (1);
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
	while (result != TRUE)
	{
		result = hungry_philo(&philosopher[index]);
		if (result == TRUE)
		{
			id = index;
			break ;
		}
		index = (index + 1) % philos;
		result = finish_philo(shared);
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
	int			index;

	gettimeofday(&shared->start_time, NULL);
	run_thread(philosopher, philos);
	monitor_thread(philosopher, shared, philos);
	reclaim_thread(philosopher, philos);
	return (1);
}