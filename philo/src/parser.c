/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:29:37 by yeongo            #+#    #+#             */
/*   Updated: 2023/02/26 11:53:27 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"
#include "utils.h"
#include "message.h"

static int	parse_by_argc(t_shared_data **shared_data, int argc)
{
	if (argc != 5 && argc != 6)
	{
		print_error_message("Invalid number of arguments");
		return (0);
	}
	*shared_data = ft_calloc(1, sizeof(t_shared_data));
	if (*shared_data == NULL)
	{
		print_error_message("Fail to allocate memory");
		return (0);
	}
	(*shared_data)->philo_info = ft_calloc(argc, sizeof(int));
	if ((*shared_data)->philo_info == NULL)
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

static int	set_info(int *philo_info, char **argv)
{
	int	index;
	int	data;

	index = 1;
	while (argv[index])
	{
		if (ft_atoi(argv[index], &data) && data > 0)
			philo_info[index - 1] = data;
		else
			return (0);
		index++;
	}
	if (philo_info[IS_LIMIT_EAT])
	{
		philo_info[MUST_EAT] = philo_info[IS_LIMIT_EAT];
		philo_info[IS_LIMIT_EAT] = 1;
	}
	return (1);
}

static int	parse_by_argv(int *philo_info, char **argv)
{
	if (is_digit_array(argv) == 0)
	{
		print_error_message("Arguments should only be numeric");
		return (0);
	}
	if (set_info(philo_info, argv) == 0)
	{
		print_error_message("Arguments must be greater than zero");
		return (0);
	}
	return (1);
}

int	parse_argument(int argc, char **argv, t_shared_data **shared_data)
{
	if (parse_by_argc(shared_data, argc))
		return (0);
	if (parse_by_argv((*shared_data)->philo_info, argv))
	{
		ft_free((void **)&(*shared_data)->philo_info);
		ft_free((void **)shared_data);
		return (0);
	}
	return (1);
}
