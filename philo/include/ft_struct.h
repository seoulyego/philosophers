/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:38:32 by yeongo            #+#    #+#             */
/*   Updated: 2023/03/12 21:40:18 by yeongo           ###   ########.fr       */
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
	int				routine;
	int				eat_count;
	int				r_fork;
	int				l_fork;
	t_time			cur_time;
	t_time			last_eat_time;
	t_shared_data	*shared;
};

struct s_shared_data
{
	int				*info;
	t_time			start_time;
	int				*forks;
	pthread_mutex_t	*m_forks;
	int				someone_die;
	pthread_mutex_t	m_someone_die;
	int				all_eat;
	pthread_mutex_t	m_all_eat;
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
	THINKING,
	EATING,
	SLEEPING,
	DIED,
	TAKE_FORK
};

enum e_fork_state
{
	AVAILABLE,
	DISABLE
};

#endif
