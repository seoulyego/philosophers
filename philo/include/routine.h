/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guest <Guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:26:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 22:47:35 by Guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "ft_struct.h"

int		philo_eating(t_philosopher *philo);
int		philo_sleeping(t_philosopher *philo);
int		philo_thinking(t_philosopher *philo);
void	*philo_routine(void *philosopher);

#endif