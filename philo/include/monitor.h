/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:03 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/14 22:16:05 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "ft_struct.h"

int		hungry_philo(t_philosopher *philo);
int		finish_philo(t_philosopher *philo);
int		monitor_philo(t_philosopher *philo);
void	check_all_eat(t_philosopher *philo);
void	set_someone_died(t_philosopher *philo);

#endif
