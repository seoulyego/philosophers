/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:47:09 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 17:25:11 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# include "ft_struct.h"

int		get_timestamp(t_time cur_time, t_time start_time);
int		print_philo(t_philosopher *philo, int routine);
void	print_error_message(char *err_msg);

#endif
