/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:10:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/02/26 13:35:04 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "utils.h"
#include "message.h"

int	init_philosopher(t_philosopher **philosopher, t_shared_data *shared_data)
{
	const int	philos = shared_data->philo_info[PHILOSOPHERS];
	int			index;

	*philosopher = ft_calloc(philos, sizeof(t_philosopher));
	if (*philosopher == NULL)
	{
		print_error_message("Fail to allocate memory");
		return (0);
	}
	index = 0;
	while (index < philos)
	{
		(*philosopher)->id = index + 1;
		(*philosopher)->shared_data = shared_data;
		index++;
	}
	return (1);
}
