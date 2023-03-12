/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:29:37 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 19:39:00 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "utils.h"
#include "message.h"
#include <string.h>

static int	parse_by_argc(t_shared_data *shared, int argc)
{
	if (argc != 5 && argc != 6)
	{
		print_error_message("Invalid number of arguments");
		return (0);
	}
	memset(shared, 0, sizeof(t_shared_data));
	shared->info = ft_calloc(argc, sizeof(int));
	if (shared->info == NULL)
	{
		print_error_message("Fail to allocate memory");
		return (0);
	}
	return (1);
}

static int	is_digit_array(char **argv)
{
	int	index_str;
	int	index_char;

	index_str = 0;
	while (argv[index_str])
	{
		index_char = 0;
		while (ft_isspace(argv[index_str][index_char]))
			index_char++;
		if (ft_issign(argv[index_str][index_char]))
			index_char++;
		while (argv[index_str][index_char])
		{
			if (ft_isdigit(argv[index_str][index_char]) == 0)
				return (0);
			index_char++;
		}
		index_str++;
	}
	return (1);
}

static int	set_info(t_shared_data *shared, char **argv)
{
	int	index;
	int	data;

	index = 1;
	while (argv[index])
	{
		if (ft_atoi(argv[index], &data) && data <= 0)
			return (0);
		shared->info[index - 1] = data;
		index++;
	}
	if (shared->info[IS_LIMIT_EAT])
	{
		shared->info[MUST_EAT] = shared->info[IS_LIMIT_EAT];
		shared->info[IS_LIMIT_EAT] = 1;
	}
	shared->forks = ft_calloc (shared->info[PHILOSOPHERS], sizeof(int));
	if (shared->forks == NULL)
		return (0);
	shared->forks_mutex = ft_calloc
		(shared->info[PHILOSOPHERS], sizeof(pthread_mutex_t));
	if (shared->forks_mutex == NULL)
		return (0);
	return (1);
}

static int	parse_by_argv(t_shared_data *shared, char **argv)
{
	if (is_digit_array(argv) == 0)
	{
		print_error_message("Arguments should only be numeric");
		return (0);
	}
	if (set_info(shared, argv) == 0)
	{
		print_error_message("Arguments must be greater than zero");
		return (0);
	}
	return (1);
}

int	parse_argument(int argc, char **argv, t_shared_data *shared)
{
	if (parse_by_argc(shared, argc))
		return (0);
	if (parse_by_argv(shared, argv))
	{
		ft_free((void **)&shared->info);
		ft_free((void **)&shared->forks);
		ft_free((void **)&shared->forks_mutex);
		return (0);
	}
	return (1);
}
