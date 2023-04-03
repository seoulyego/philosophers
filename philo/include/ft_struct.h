/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:52:31 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 14:45:31 by yeongo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

# include <pthread.h>
# include <sys/time.h>

# define F_NUM 3

typedef struct s_philosopher	t_philosopher;
typedef struct s_shared_data	t_shared_data;
typedef struct s_info			t_info;
typedef struct timeval			t_time;

struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				routine;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	t_time			cur_time;

	pthread_mutex_t	m_last_eat_time;
	t_time			last_eat_time;

	t_shared_data	*shared;
};

struct s_shared_data
{
	int				*info;
	t_time			start_time;
	int				(*f_routine[F_NUM])(t_philosopher *);

	pthread_mutex_t	*m_forks;
	int				*forks;

	pthread_mutex_t	m_end_philo;
	int				end_philo;

	pthread_mutex_t	m_eat_complete;
	int				eat_complete;

	pthread_mutex_t	m_print;
};

enum e_info
{
	PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	IS_LIMIT_EAT,
	MUST_EAT
};

enum e_routine
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORKS
};

enum e_fork_state
{
	AVAILABLE,
	DISABLE
};

enum e_bool
{
	FALSE,
	TRUE
};

enum e_result
{
	FAIL,
	SUCCESS
};

#endif