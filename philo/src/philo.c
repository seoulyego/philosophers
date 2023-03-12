/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:02:19 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 20:32:07 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "routine.h"
#include "message.h"

void	set_up_routines(int (*f_routine[F_NUM])(t_philosopher *))
{
	f_routine[0] = the_thinker;
	f_routine[1] = take_forks;
	f_routine[2] = dreams_come_true;
}

int	init_f_index(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		return (0);
	else
		return (1);
}

int	get_routines(t_philosopher *philo);

void	*philo_routine(void *philosopher)
{
	t_philosopher	*philo;
	static int		(*f_routine[F_NUM])(t_philosopher *);

	philo = (t_philosopher *)philosopher;
	philo->cur_time = philo->shared->start_time;
	philo->last_eat_time = philo->shared->start_time;
	philo->routine = init_f_index(philo);
	set_up_routines(f_routine);
	while (1)
	{
		f_routine[philo->routine](philo);
		get_routines(philo);
	}
	return (NULL);
}

int	create_thread(t_philosopher *philosopher)
{
	const int	philos = philosopher->shared->info[PHILOSOPHERS];
	int			index;

	index = 0;
	gettimeofday(&philosopher->shared->start_time, NULL);
	while (index < philos)
	{
		if (pthread_create(&philosopher[index].thread, \
				NULL, philo_routine, philosopher) != 0)
			return (0);
		index++;
	}
	return (1);
}
