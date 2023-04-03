/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:15:41 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/03 16:16:58 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "message.h"

static int	set_eat_count(t_philosopher *philo, t_shared_data *shared)
{
	philo->eat_count++;
	pthread_mutex_lock(&philo->m_last_eat_time);
	philo->last_eat_time = philo->cur_time;
	pthread_mutex_unlock(&philo->m_last_eat_time);
	if (shared->info[IS_LIMIT_EAT]
		&& philo->eat_count == shared->info[MUST_EAT])
	{
		pthread_mutex_lock(&shared->m_eat_complete);
		shared->eat_complete++;
		if (shared->eat_complete == shared->info[PHILOS])
		{
			pthread_mutex_lock(&shared->m_end_philo);
			shared->end_philo = TRUE;
			pthread_mutex_unlock(&shared->m_end_philo);
			pthread_mutex_unlock(&shared->m_eat_complete);
			return (1);
		}
		pthread_mutex_unlock(&shared->m_eat_complete);
	}
	return (0);
}

int	eat_philo(t_philosopher *philo, t_shared_data *shared)
{
	if (print_routine(philo, shared, EATING) == FAIL
		|| set_eat_count(philo, shared)
		|| spend_time(philo, shared->info[TIME_TO_EAT]) == FAIL)
	{
		pthread_mutex_unlock(&shared->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&shared->m_forks[philo->r_fork]);
		return (FAIL);
	}
	return (SUCCESS);
}
