/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:13:42 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/31 10:55:47 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>

static int	ft_issign_for_atoi(int c, int *sign)
{
	if (ft_issign(c))
	{
		if (c == '-')
			*sign *= -1;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str, int *result)
{
	int			sign;
	int			in_range;
	long long	result_tmp;

	sign = 1;
	in_range = 1;
	result_tmp = 0;
	while (ft_isspace(*str))
		str++;
	if (ft_issign_for_atoi(*str, &sign))
		str++;
	while (ft_isdigit(*str))
	{
		result_tmp = 10 * result_tmp + (sign * (*str - '0'));
		if (result_tmp < INT_MIN || result_tmp > INT_MAX)
			in_range = 0;
		str++;
	}
	*result = result_tmp;
	return (in_range);
}
