/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:06:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 17:31:44 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"

static int	take_right_fork(t_philosopher *philo)
{
	return (1);
}

static int	take_left_fork(t_philosopher *philo);

int	take_forks(t_philosopher *philo)
{
	if (take_right_fork(philo) == 0)
		return (0);
	if (take_left_fork(philo) == 0)
		return (0);
	return (1);
}
