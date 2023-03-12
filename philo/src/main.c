/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:21:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 19:43:54 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "parser.h"
#include "init.h"
#include "philo.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_philosopher	*philosopher;
	t_shared_data	shared;

	if (parse_argument(argc, argv, &shared) == 0)
		return (1);
	if (init_philosopher(&philosopher, &shared) == 0)
	{
		if (philosopher != NULL)
			ft_free((void **)philosopher);
		return (1);
	}
	if (create_thread(philosopher) == 0)
		return (1);
	return (0);
}
