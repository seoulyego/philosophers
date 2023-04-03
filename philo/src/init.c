/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:10:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 14:52:26 by yeongo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "message.h"

static int	init_mutex(t_philosopher *philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	index = 0;
	while (index < philos)
	{
		if (((pthread_mutex_init(&philosopher[index].m_last_eat_time, NULL)
				|| pthread_mutex_init(&(shared->m_forks[index]), NULL))) != 0)
			return (FAIL);
		index++;
	}
	if (((pthread_mutex_init(&(shared->m_end_philo), NULL)
			|| pthread_mutex_init(&(shared->m_eat_complete), NULL)
			|| pthread_mutex_init(&(shared->m_print), NULL))) != 0)
		return (FAIL);
	return (SUCCESS);
}

int	init_philosopher(t_philosopher **philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	*philosopher = ft_calloc(philos, sizeof(t_philosopher));
	if (*philosopher == NULL)
	{
		print_error_message("Fail to allocate memory");
		return (FAIL);
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
	if (init_mutex(*philosopher, shared) == FAIL)
	{
		print_error_message("Fail to init mutex");
		ft_free((void **)philosopher);
		return (FAIL);
	}
	return (SUCCESS);
}
