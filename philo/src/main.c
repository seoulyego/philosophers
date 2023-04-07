/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:46:13 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/08 03:32:21 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "init.h"
#include "thread.h"
#include <pthread.h>
#include <stdlib.h>

void	destroy_all_mutex(t_philosopher *philosopher, t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	index = 0;
	while (index < philos)
	{
		pthread_mutex_destroy(&philosopher[index].m_last_eat_time);
		pthread_mutex_destroy(&shared->m_forks[index]);
		index++;
	}
	pthread_mutex_destroy(&shared->m_end_philo);
	pthread_mutex_destroy(&shared->m_eat_complete);
	pthread_mutex_destroy(&shared->m_print);
}

void	free_all_memories(t_philosopher **philosopher, t_shared_data *shared)
{
	free(shared->forks);
	free(shared->m_forks);
	free(shared->info);
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
	create_thread(philosopher, &shared);
	destroy_all_mutex(philosopher, &shared);
	free_all_memories(&philosopher, &shared);
	return (0);
}
