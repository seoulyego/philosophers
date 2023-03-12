/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:21:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/05 17:37:43 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "parser.h"
#include "init.h"
#include "philo.h"

int	main(int argc, char **argv)
{
	t_philosopher	*philosopher;
	t_shared_data	*shared_data;

	if (parse_argument(argc, argv, &shared_data) == 0)
		return (1);
	if (init_philosopher(&philosopher, shared_data) == 0)
		return (1);
	if (create_thread(philosopher) == 0)
		return (1);
	return (0);
}
