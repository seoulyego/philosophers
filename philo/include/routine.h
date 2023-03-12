/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:32:07 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 20:18:01 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "ft_struct.h"

int	take_forks(t_philosopher *philo);
int	take_left_fork(t_philosopher *philo);
int	take_right_fork(t_philosopher *philo);
int	get_down_forks(t_philosopher *philo);
int	get_down_left_fork(t_philosopher *philo);
int	get_down_right_fork(t_philosopher *philo);
int	eating(t_philosopher *philo);
int	dreams_come_true(t_philosopher *philo);
int	the_thinker(t_philosopher *philo);

#endif
