/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:47:09 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/08 06:53:03 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# include "ft_struct.h"

long	get_timestamp(t_time cur_time, t_time start_time);
int		print_routine(t_philosopher *philo, t_shared_data *shared, int routine);
void	print_death(t_philosopher *philo, t_shared_data *shared);
void	print_error_message(char *err_msg);

#endif
