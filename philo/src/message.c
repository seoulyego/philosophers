/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:40:23 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 17:25:01 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "utils.h"

int	get_timestamp(t_time cur_time, t_time start_time)
{
	return ((cur_time.tv_sec - start_time.tv_sec) * 1000
		+ (cur_time.tv_usec - start_time.tv_usec) / 1000);
}

int	print_philo(t_philosopher *philo, int routine);

void	print_error_message(char *err_msg)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
