/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:19:32 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 19:09:57 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	sle_ep(time_t time, t_infos *infos)
{
	time_t		start;

	start = get_time();
	while (get_time() - start < time && !safe_access(&infos->dead_lock,
			&infos->philo_dead, FALSE, READ))
		usleep(100);
}

void	life_cycle_log(t_philo *philo, char *log, int mode)
{
	t_infos		*infos;
	time_t		time_stamp;

	infos = philo->infos;
	pthread_mutex_lock(&infos->print_lock);
	if (mode == TRUE)
	{
		time_stamp = get_time() - infos->start_time;
		printf("%-12ld %-4d %s\n", time_stamp, philo->tid, log);
	}
	else if (!safe_access(&infos->dead_lock, &infos->philo_dead, FALSE, READ))
	{
		time_stamp = get_time() - infos->start_time;
		printf("%-12ld %-4d %s\n", time_stamp, philo->tid, log);
	}
	pthread_mutex_unlock(&infos->print_lock);
}

static void	dine_safely(t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&philo->philo_fork);
	life_cycle_log(philo, FORK, FALSE);
	if (philo->tid == next->tid)
	{
		pthread_mutex_unlock(&philo->philo_fork);
		return ;
	}
	pthread_mutex_lock(&next->philo_fork);
	life_cycle_log(philo, FORK, FALSE);
	life_cycle_log(philo, EAT, FALSE);
	safe_access(&philo->meal_lock, &philo->last_meal, get_time(), WRITE);
	sle_ep(philo->infos->eat_time, philo->infos);
	pthread_mutex_unlock(&philo->philo_fork);
	pthread_mutex_unlock(&next->philo_fork);
}

void	*life_cycle(void *value)
{
	int			meals;
	t_philo		*philo;
	t_infos		*infos;

	philo = value;
	infos = philo->infos;
	if ((philo->tid % 2) == 0)
		sle_ep(infos->eat_time, infos);
	meals = philo->infos->meals_num;
	while ((meals == -1 || meals--) && !safe_access(&infos->dead_lock,
			&infos->philo_dead, FALSE, READ))
	{
		dine_safely(philo, philo->next);
		if (philo->tid == philo->next->tid)
			return (NULL);
		if (meals == FALSE)
		{
			safe_access(&infos->dead_lock, &infos->philos_full, FALSE, INCR);
			return (NULL);
		}
		life_cycle_log(philo, SLEEP, FALSE);
		sle_ep(infos->sleep_time, infos);
		life_cycle_log(philo, THINK, FALSE);
	}
	return (NULL);
}
