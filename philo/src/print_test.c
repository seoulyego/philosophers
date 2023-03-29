/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:40:14 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 16:40:50 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"

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