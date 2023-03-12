/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:38:32 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/05 20:23:29 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

# include <pthread.h>
# include <sys/time.h>

# define F_NUM 7

typedef struct s_philosopher	t_philosopher;
typedef struct s_shared_data	t_shared_data;
typedef struct timeval			t_time;

struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				fork_state;
	pthread_mutex_t	fork_state_mutex;
	t_time			start_time;
	t_time			cur_time;
	t_time			last_eat_time;
	int				eat_count;
	int				routine;
	t_shared_data	*shared_data;
};

struct s_shared_data
{
	int				*philo_info;
	int				someone_die;
	pthread_mutex_t	someone_die_mutex;
	int				all_eat;
	pthread_mutex_t	all_eat_mutex;
};

enum e_philo_info
{
	PHILOSOPHERS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	IS_LIMIT_EAT,
	MUST_EAT
};

#endif
