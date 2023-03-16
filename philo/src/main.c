/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:21:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/16 18:57:27 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "init.h"
#include "philo.h"
#include "utils.h"

static void	destroy_mutex(t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	index = 0;
	while (index < philos)
	{
		pthread_mutex_destroy(&shared->m_forks[index], NULL);
		index++;
	}
	pthread_mutex_destroy(&shared->m_someone_die, NULL);
	pthread_mutex_destroy(&shared->m_all_eat, NULL);
	pthread_mutex_destroy(&shared->m_print, NULL);
}

static void	free_all_heap(t_philosopher **philosopher, t_shared_data *shared)
{
	ft_free(shared->info);
	ft_free(shared->forks);
	ft_free(shared->m_forks);
	ft_free(philosopher);
}

void	destroy_and_free(t_philosopher **philosopher, t_shared_data *shared)
{
	destroy_mutex(shared);
	free_all_heap(philosopher, shared);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philosopher;
	t_shared_data	shared;

	if (parse_argument(argc, argv, &shared) == 0)
		return (1);
	if (init_philosopher(&philosopher, &shared) == 0)
		return (1);
	if (create_thread(philosopher) == 0)
		return (1);
	destroy_mutex_and_free_heap(&philosopher, &shared);
	return (0);
}
