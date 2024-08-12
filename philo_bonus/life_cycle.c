/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:19:32 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/11 19:11:53 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	sle_ep(time_t time, t_infos *infos)
{
	time_t		start;

	start = get_time();
	while (get_time() - start < time /* && !infos->philo_dead */)
		usleep(100);
}

time_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	life_cycle_log(t_philo *philo, char *log, int mode)
{
	if (LOCK)
		return (ERROR);
	if (mode == TRUE)
		printf("%-12ld %-4d %s\n", get_time() - philo->infos->start_time,
			philo->tid, log);
	else if (philo->infos->philo_dead)
		printf("%-12ld %-4d %s\n", get_time() - philo->infos->start_time,
			philo->tid, log);
	if (UNLOCK)
		return (ERROR);
	return (TRUE);
}

int	dine_safely(t_philo *philo, t_philo *next)
{
	if (protected_lock(&philo->philo_fork, NULL, LOCK) == ERROR)
		return (ERROR);
	if (life_cycle_log(philo, FORK, FALSE) == ERROR)
		return (protected_lock(&philo->philo_fork, NULL, UNLOCK), ERROR);
	if (philo->tid == next->tid || protected_lock(&next->philo_fork,
			NULL, LOCK) == ERROR)
		return (protected_lock(&philo->philo_fork, NULL, UNLOCK), ERROR);
	if (life_cycle_log(philo, FORK, FALSE) == ERROR
		|| life_cycle_log(philo, EAT, FALSE) == ERROR)
		return (protected_lock(&philo->philo_fork, &next->philo_fork,
				UNLOCK), ERROR);
	if (safe_access(&philo->meal_lock, &philo->last_meal,
			get_time(), WRITE) == ERROR)
		return (protected_lock(&philo->philo_fork, &next->philo_fork,
				UNLOCK), ERROR);
	sle_ep(philo->infos->eat_time, philo->infos);
	if (protected_lock(&philo->philo_fork, &next->philo_fork, UNLOCK) == ERROR)
		return (ERROR);
	return (TRUE);
}

void	*life_cycle(void *value)
{
	int			meals;
	t_philo		*philo;

	philo = value;
	meals = philo->infos->meals_num;
	if (!(philo->tid % 2))
		sle_ep(philo->infos->eat_time, philo->infos);
	while ((meals == -1 || meals--) && !philo->infos->philo_dead)
	{
		if (dine_safely(philo, philo->next) == ERROR)
			return (NULL);
		if (meals == FALSE)
			break ;
		if (life_cycle_log(philo, SLEEP, FALSE) == ERROR)
			return (NULL);
		sle_ep(philo->infos->sleep_time, philo->infos);
		if (life_cycle_log(philo, THINK, FALSE) == ERROR)
			return (NULL);
	}
	return (philo->infos->philos_full++, philo);
}
