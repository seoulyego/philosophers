/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:46:13 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 18:03:57 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "init.h"
#include "thread.h"

int	main(int argc, char **argv)
{
	t_philosopher	*philosopher;
	t_shared_data	shared;

	if (parse_argument(argc, argv, &shared) == 0)
		return (1);
	if (init_philosopher(&philosopher, &shared) == 0)
		return (1);
	create_thread(philosopher, &shared);
	return (0);
}