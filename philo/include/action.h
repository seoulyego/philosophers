/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:13:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/30 16:17:33 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# include "ft_struct.h"

int		spend_time(t_philosopher *philo, int target_time);
int		take_forks(t_philosopher *philo);
int		eat_philo(t_philosopher *philo);
int		get_down_forks(t_philosopher *philo);
int		philo_eating(t_philosopher *philo);
int		philo_sleeping(t_philosopher *philo);
int		philo_thinking(t_philosopher *philo);

#endif