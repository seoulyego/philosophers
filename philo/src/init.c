/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:10:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/27 15:53:42 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "message.h"
#include <pthread.h>

static int	init_mutex(t_philosopher *philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	index = 0;
	while (index < philos)
	{
		if (pthread_mutex_init(&philosopher[index].m_last_eat_time, NULL))
			return (0);
		if (pthread_mutex_init(&(shared->m_forks[index]), NULL) != 0)
			return (0);
		index++;
	}
	if (pthread_mutex_init(&(shared->m_start_time), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(shared->m_end_philo), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(shared->m_all_eat), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(shared->m_print), NULL) != 0)
		return (0);
	return (1);
}

int	init_philosopher(t_philosopher **philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	*philosopher = ft_calloc(philos, sizeof(t_philosopher));
	if (*philosopher == NULL)
	{
		print_error_message("Fail to allocate memory");
		return (0);
	}
	index = 0;
	while (index < philos)
	{
		(*philosopher)[index].id = index + 1;
		(*philosopher)[index].r_fork = index;
		(*philosopher)[index].l_fork = (index + 1) % philos;
		(*philosopher)[index].shared = shared;
		index++;
	}
	if (init_mutex(*philosopher, shared) == 0)
	{
		ft_free((void **)philosopher);
		return (0);
	}
	return (1);
}
