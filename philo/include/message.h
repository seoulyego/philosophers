/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:47:09 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 20:52:38 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# include "ft_struct.h"

int		print_routine(t_philosopher *philo, t_shared_data *shared, int routine);
int		print_death(t_philosopher *philo, t_shared_data *shared);
void	print_error_message(char *err_msg);

#endif
