/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:19:32 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/08 22:14:00 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	sle_ep(time_t time, t_infos *infos)
{
	time_t		start;

	start = get_time();
	while (get_time() - start < time && !safe_access(&infos->dead_lock,
				&infos->philo_dead, FALSE, READ))
		usleep(10);
}

time_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	life_cycle_log(t_philo *philo, int mode)
{
	int			philo_dead;
	time_t		time;

	time = get_time() - philo->infos->start_time;
	philo_dead = safe_access(&philo->infos->dead_lock,
			&philo->infos->philo_dead, FALSE, READ);
	if (philo_dead)
	{
		if (mode == 5)
			printf("%-12ld %-4d %s\n", time, philo->tid, DIED);
		return (ERROR);
	}
	if (protected_lock(&philo->infos->print_lock, NULL, LOCK) == ERROR)
		return (ERROR);
	if (mode == 1)
		printf("%-12ld %-4d %s\n", time, philo->tid, FORK);
	else if (mode == 2)
		printf("%-12ld %-4d %s\n", time, philo->tid, EAT);
	else if (mode == 3)
		printf("%-12ld %-4d %s\n", time, philo->tid, SLEEP);
	else if (mode == 4)
		printf("%-12ld %-4d %s\n", time, philo->tid, THINK);
	if (protected_lock(&philo->infos->print_lock, NULL, UNLOCK) == ERROR)
		return (ERROR);
	return (TRUE);
}

int	dine_safely(t_philo *philo, t_philo *next)
{
	if (protected_lock(&philo->philo_fork, NULL, LOCK) == ERROR)
		return (ERROR);
	if (life_cycle_log(philo, 1) == ERROR)
		return (protected_lock(&philo->philo_fork, NULL, UNLOCK), ERROR);
	if (protected_lock(&next->philo_fork, NULL, LOCK) == ERROR)
		return (protected_lock(&philo->philo_fork, NULL, UNLOCK), ERROR);
	if (life_cycle_log(philo, 1) == ERROR || life_cycle_log(philo, 2) == ERROR)
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
	t_philo		*philo;

	philo = value;
	if (!(philo->tid % 2))
		sle_ep(philo->infos->eat_time, philo->infos);
	while (TRUE)
	{
		if (safe_access(&philo->infos->dead_lock,
				&philo->infos->philo_dead, FALSE, READ))
			return (NULL);
		if (dine_safely(philo, philo->next) == ERROR)
			return (NULL);
		if (life_cycle_log(philo, 3) == ERROR)
			return (NULL);
		sle_ep(philo->infos->sleep_time, philo->infos);
		if (life_cycle_log(philo, 4) == ERROR)
			return (NULL);
	}
	return (philo);
}
