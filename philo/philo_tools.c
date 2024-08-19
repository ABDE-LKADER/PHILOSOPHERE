/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:47:50 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 18:48:23 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

time_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	join_threads(t_philo *philo, t_infos *infos)
{
	while (philo)
	{
		pthread_join(philo->thread_id, NULL);
		if (philo->tid == infos->philo_num)
			break ;
		philo = philo->next;
	}
}

long	safe_access(pthread_mutex_t *mutex, long *value, long new, int mode)
{
	long		fetch;

	fetch = 0;
	pthread_mutex_lock(mutex);
	if (mode == READ)
		fetch = *value;
	else if (mode == WRITE)
		*value = new;
	else if (mode == INCR)
		(*value)++;
	pthread_mutex_unlock(mutex);
	return (fetch);
}

void	cleanup(t_philo *philo, t_infos *infos)
{
	join_threads(philo, infos);
	pthread_mutex_destroy(&infos->dead_lock);
	pthread_mutex_destroy(&infos->print_lock);
	while (philo)
	{
		pthread_mutex_destroy(&philo->philo_fork);
		pthread_mutex_destroy(&philo->meal_lock);
		if (philo->tid == infos->philo_num)
		{
			free(philo);
			break ;
		}
		free(philo);
		philo = philo->next;
	}
}
