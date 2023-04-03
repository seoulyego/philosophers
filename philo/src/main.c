/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:46:13 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 19:21:08 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "init.h"
#include "thread.h"

// void	destroy_all_mutex(t_philosopher *philosopher, t_shared_data *shared)
// {

// }

int	main(int argc, char **argv)
{
	t_philosopher	*philosopher;
	t_shared_data	shared;

	if (parse_argument(argc, argv, &shared) == FAIL)
		return (1);
	if (init_philosopher(&philosopher, &shared) == FAIL)
		return (1);
	create_thread(philosopher, &shared);
	return (0);
}
