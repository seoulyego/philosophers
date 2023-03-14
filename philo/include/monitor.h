/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:03 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/14 20:17:49 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "ft_struct.h"

int		hungry_philo(t_philosopher *philo);
int		finish_philo(t_philosopher *philo);
int		monitor_philo(t_philosopher *philo);
void	increase_eat_count(t_philosopher *philo);
void	check_someone_died(t_philosopher *philo);

#endif
