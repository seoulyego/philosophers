/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:40:14 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/31 10:54:54 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include <stdio.h>

void	print_info(int *info)
{
	int	index;

	index = 0;
	while (index < MUST_EAT + 1)
	{
		printf("info[%d] %d\n", index, info[index]);
		index++;
	}
}

void	print_forks(t_shared_data *shared)
{
	const int	philos = shared->info[PHILOS];
	int			index;

	index = -1;
	while (index < philos)
	{
		printf("fork[%d] is %d\n", index, shared->forks[index]);
		index++;
	}
}
