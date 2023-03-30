/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:28 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/30 16:28:41 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "ft_struct.h"

int	monitor_starving(t_philosopher *philo, t_shared_data *shared);
int	monitor_finish(t_shared_data *shared);

#endif