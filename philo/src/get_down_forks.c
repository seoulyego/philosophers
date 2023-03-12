/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_down_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:05:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 17:30:19 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"

static int	get_down_right_fork(t_philosopher *philo);

static int	get_down_left_fork(t_philosopher *philo);

int	get_down_forks(t_philosopher *philo)
{
	if (get_down_right_fork(philo) == 0)
		return (0);
	if (get_down_left_fork(philo) == 0)
		return (0);
	return (1);
}
