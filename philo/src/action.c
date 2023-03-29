/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guest <Guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:42:53 by Guest             #+#    #+#             */
/*   Updated: 2023/03/29 22:55:19 by Guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

int	philo_eating(t_philosopher *philo)
{
	if (take_forks(philo) && eat_philo(philo) && get_down_forks(philo) == 0)
		return (0);
	return (1);
}

int	philo_sleeping(t_philosopher *philo);

int	philo_thinking(t_philosopher *philo);