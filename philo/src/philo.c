/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:02:19 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/16 15:50:06 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "monitor.h"

void	set_up_routines(int (*f_routine[F_NUM])(t_philosopher *))
{
	f_routine[0] = philo_think;
	f_routine[1] = philo_eating;
	f_routine[2] = philo_sleep;
}

int	init_f_index(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		return (0);
	else if (philo->id == philo->shared->info[PHILOS])
		return (0);
	else
		return (1);
}

int	get_routines(t_philosopher *philo)
{
	if (philo->routine == THINKING)
		philo->routine = EATING;
	else if (philo->routine == EATING)
		philo->routine = SLEEPING;
	else if (philo->routine == SLEEPING)
		philo->routine = THINKING;
	return (1);
}

void	*philo_routine(void *philosopher)
{
	t_philosopher	*philo;
	static int		(*f_routine[F_NUM])(t_philosopher *);

	philo = (t_philosopher *)philosopher;
	philo->cur_time = philo->shared->start_time;
	philo->last_eat_time = philo->shared->start_time;
	philo->routine = init_f_index(philo);
	if (philo->id == 1)
		set_up_routines(f_routine);
	while (1)
	{
		if (monitor_philo(philo) == TRUE)
			break ;
		if (f_routine[philo->routine](philo) == 0)
			break ;
		get_routines(philo);
	}
	return (NULL);
}

int	create_thread(t_philosopher *philosopher)
{
	const int	philos = philosopher->shared->info[PHILOS];
	int			index;

	index = 0;
	gettimeofday(&philosopher->shared->start_time, NULL);
	while (index < philos)
	{
		if (pthread_create(&philosopher[index].thread, \
				NULL, philo_routine, &philosopher[index]) != 0)
			return (0);
		index++;
	}
	index = 0;
	while (index < philos)
	{
		pthread_join(philosopher[index].thread, NULL);
		index++;
	}
	return (1);
}
