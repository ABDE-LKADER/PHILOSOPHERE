/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:19:32 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 07:18:43 by abadouab         ###   ########.fr       */
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

time_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
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

void	dine_safely(t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&philo->philo_fork);
	life_cycle_log(philo, FORK, FALSE);
	if (philo->tid == next->tid)
		return ((void)pthread_mutex_unlock(&philo->philo_fork));
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

	philo = value;
	meals = philo->infos->meals_num;
	if (!(philo->tid % 2))
		sle_ep(philo->infos->eat_time, philo->infos);
	while ((meals == -1 || meals--) && !safe_access(&philo->infos->dead_lock,
			&philo->infos->philo_dead, FALSE, READ))
	{
		dine_safely(philo, philo->next);
		if (philo->tid == philo->next->tid)
			return (NULL);
		if (meals == FALSE)
			break ;
		life_cycle_log(philo, SLEEP, FALSE);
		sle_ep(philo->infos->sleep_time, philo->infos);
		life_cycle_log(philo, THINK, FALSE);
	}
	return (safe_access(&philo->infos->dead_lock,
			&philo->infos->philos_full, FALSE, INCR), philo);
}
