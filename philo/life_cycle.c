/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:19:32 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/06 21:19:53 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	_sleep(time_t time)
{
	time_t		start;

	start  = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	*life_cycle(void *value)
{
	t_philo		*philo;

	philo = (t_philo *)value;
	if (!(philo->tid % 2))
		_sleep(philo->infos->eat_time);
	while (!philo->infos->philo_dead)
	{
		pthread_mutex_lock(&philo->my_fork);
		life_cycle_log(philo, N1);
		pthread_mutex_lock(&philo->next->my_fork);
		life_cycle_log(philo, N1);
		life_cycle_log(philo, N2);
		pthread_mutex_lock(&philo->safe_check);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->safe_check);
		_sleep(philo->infos->eat_time);
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_unlock(&philo->next->my_fork);
		life_cycle_log(philo, N3);
		_sleep(philo->infos->sleep_time);
		life_cycle_log(philo, N4);
	}
	return (philo);
}
