/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:38:32 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/29 10:23:46 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

# include <pthread.h>
# include <sys/time.h>

# define F_NUM 3

typedef struct s_philosopher	t_philosopher;
typedef struct s_shared_data	t_shared_data;
typedef struct timeval			t_time;

struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				routine;
	int				eat_count;
	int				r_fork;
	int				l_fork;
	t_time			cur_time;
	// long			timestamp;
	t_time			last_eat_time;
	pthread_mutex_t	m_last_eat_time;
	t_shared_data	*shared;
};

struct s_shared_data
{
	int				*info;
	int				*forks;
	pthread_mutex_t	*m_forks;
	t_time			start_time;
	pthread_mutex_t	m_start_time;
	int				end_philo;
	pthread_mutex_t	m_end_philo;
	int				all_eat;
	pthread_mutex_t	m_all_eat;
	pthread_mutex_t	m_print;
};

enum e_philo_info
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
	DIED,
	TAKE_FORK
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

#endif
