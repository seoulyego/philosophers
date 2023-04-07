/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:46:13 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/08 07:00:41 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "init.h"
#include "thread.h"
#include <pthread.h>
#include <stdlib.h>

static int	destroy_all_mutex(t_philosopher *philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	index = 0;
	while (index < philos)
	{
		if (pthread_mutex_destroy(&philosopher[index].m_last_eat_time) > 0)
			return (FAIL);
		if (pthread_mutex_destroy(&shared->m_forks[index]) > 0)
			return (FAIL);
		index++;
	}
	if (pthread_mutex_destroy(&shared->m_end_philo) > 0)
		return (FAIL);
	if (pthread_mutex_destroy(&shared->m_eat_complete) > 0)
		return (FAIL);
	if (pthread_mutex_destroy(&shared->m_print) > 0)
		return (FAIL);
	return (SUCCESS);
}

static void	free_all_memory(t_philosopher **philosopher, t_shared_data *shared)
{
	free(shared->forks);
	shared->forks = NULL;
	free(shared->m_forks);
	shared->m_forks = NULL;
	free(shared->info);
	shared->info = NULL;
	free(*philosopher);
	*philosopher = NULL;
}

int	main(int argc, char **argv)
{
	t_philosopher	*philosopher;
	t_shared_data	shared;

	if (parse_argument(argc, argv, &shared) == FAIL)
		return (1);
	if (init_philosopher(&philosopher, &shared) == FAIL)
		return (1);
	if (create_thread(philosopher, &shared) == FAIL)
		return (1);
	if (destroy_all_mutex(philosopher, &shared) == FAIL)
		return (1);
	free_all_memory(&philosopher, &shared);
	return (0);
}
