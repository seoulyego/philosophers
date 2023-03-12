/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:02:19 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/05 18:53:29 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include <pthread.h>
#include <sys/time.h>

void	set_up_routines(int (*f_routine[F_NUM])(t_philosopher *))
{
	;
}

int	init_f_index(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
		return (0);
	else
		return (1);
}

void	*philo_routine(void *philosopher)
{
	t_philosopher	*philo;
	static int		(*f_routine[F_NUM])(t_philosopher *);

	philo = (t_philosopher *)philosopher;
	gettimeofday(&philo->start_time, NULL);
	philo->routine = init_f_index(philo);
	set_up_routines(f_routine);
	while (1)
	{
		f_routine[philo->routine](philo);
	}
	return (NULL);
}

int	create_thread(t_philosopher *philosopher)
{
	const int	philos = philosopher->shared_data->philo_info[PHILOSOPHERS];
	int			index;

	index = 0;
	while (index < philos)
	{
		if (pthread_create(&philosopher[index].thread, \
				NULL, philo_routine, philosopher) != 0)
			return (0);
		index++;
	}
	return (1);
}
