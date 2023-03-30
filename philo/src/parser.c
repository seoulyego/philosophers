/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:29:37 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/30 17:33:04 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "message.h"
#include <string.h>

static int	parse_by_argc(t_shared_data *shared, int argc)
{
	if (argc != 5 && argc != 6)
	{
		print_error_message("Invalid number of arguments");
		return (FAIL);
	}
	memset(shared, 0, sizeof(t_shared_data));
	shared->info = ft_calloc(argc, sizeof(int));
	if (shared->info == NULL)
	{
		print_error_message("Fail to allocate memory");
		return (FAIL);
	}
	return (SUCCESS);
}

static int	is_digit_array(char **argv)
{
	int	index_str;
	int	index_char;

	index_str = 1;
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
				return (FAIL);
			index_char++;
		}
		index_str++;
	}
	return (SUCCESS);
}

static int	set_info(t_shared_data *shared, char **argv)
{
	int	index;
	int	data;

	index = 0;
	while (argv[++index])
	{
		if (ft_atoi(argv[index], &data) && data <= 0)
			return (FAIL);
		shared->info[index - 1] = data;
	}
	if (shared->info[IS_LIMIT_EAT])
	{
		shared->info[MUST_EAT] = shared->info[IS_LIMIT_EAT];
		shared->info[IS_LIMIT_EAT] = 1;
	}
	shared->forks = ft_calloc(shared->info[PHILOS], sizeof(int));
	if (shared->forks == NULL)
		return (FAIL);
	shared->m_forks = ft_calloc(shared->info[PHILOS], sizeof(pthread_mutex_t));
	if (shared->m_forks == NULL)
	{
		ft_free((void **)&shared->forks);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	parse_by_argv(t_shared_data *shared, char **argv)
{
	if (is_digit_array(argv) == FAIL)
	{
		print_error_message("Arguments should only be numeric");
		return (FAIL);
	}
	if (set_info(shared, argv) == FAIL)
	{
		print_error_message("Arguments must be greater than zero");
		return (FAIL);
	}
	return (SUCCESS);
}

int	parse_argument(int argc, char **argv, t_shared_data *shared)
{
	if (parse_by_argc(shared, argc) == FAIL)
		return (FAIL);
	if (parse_by_argv(shared, argv) == FAIL)
	{
		ft_free((void **)&shared->info);
		return (FAIL);
	}
	return (SUCCESS);
}
