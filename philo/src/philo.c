/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:02:19 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 10:10:57 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "monitor.h"
#include <unistd.h>

void	set_up_routines(int (*f_routine[F_NUM])(t_philosopher *))
{
	f_routine[EATING] = philo_eating;
	f_routine[SLEEPING] = philo_sleep;
	f_routine[THINKING] = philo_think;
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
	if (finish_philo(philo->shared) == TRUE)
		return (0);
	else if (philo->routine == EATING)
		philo->routine = SLEEPING;
	else if (philo->routine == SLEEPING)
		philo->routine = THINKING;
	else if (philo->routine == THINKING)
		philo->routine = EATING;
	return (1);
}

void	*philo_routine(void *philosopher)
{
	t_philosopher	*philo;
	static int		(*f_routine[F_NUM])(t_philosopher *);

	philo = (t_philosopher *)philosopher;
	philo->cur_time = philo->shared->start_time;
	philo->last_eat_time = philo->shared->start_time;
	philo->routine = EATING;
	if (philo->id == 1)
		set_up_routines(f_routine);
	if (philo->id % 2 == 0)
		usleep(100);
	while (finish_philo(philo->shared) != TRUE)
	{
		if (f_routine[philo->routine](philo) == FALSE)
			break ;
		if (get_routines(philo) == 0)
			break ;
	}
	return (NULL);
}

int	create_thread(t_philosopher *philosopher, t_shared_data *shared)
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
	while (monitor_philo(shared) != TRUE)
		usleep(100);
	index = 0;
	while (index < philos)
	{
		pthread_detach(philosopher[index].thread);
		// pthread_join(philosopher[index].thread, NULL);
		index++;
	}
	return (1);
}
