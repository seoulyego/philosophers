/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:01:52 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 20:52:28 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"

int	philo_eating(t_philosopher *philo);

int	philo_sleeping(t_philosopher *philo);

int	philo_thinking(t_philosopher *philo);

void	set_f_routine(int (*f_routine[F_NUM])(t_philosopher *))
{
	f_routine[EATING] = philo_eating;
	f_routine[SLEEPING] = philo_sleeping;
	f_routine[THINKING] = philo_thinking;
}

void	init_philo_time(t_philosopher *philo, t_shared_data *shared)
{
	philo->cur_time = shared->start_time;
	philo->last_eat_time = shared->start_time;
}

void	*philo_routine(void *philosopher)
{
	t_philosopher	*philo;
	t_shared_data	*shared = philo->shared;
	static int		(*f_routine[F_NUM])(t_philosopher *);

	philo = philosopher;
	if (philo->id == 1)
		set_f_routine(philo);
	init_philo_time(philo, philo->shared);
	while (finish_philo(shared) != TRUE)
	{
		if (f_routine[philo->routine](philo) == 0)
			break ;
		if (print_routine(philo, philo->shared, philo->routine))
			break ;
		philo->routine = (philo->routine + 1) % F_NUM;
	}
	return (NULL);
}