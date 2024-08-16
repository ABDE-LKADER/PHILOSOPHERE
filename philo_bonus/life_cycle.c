/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:19:32 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/16 11:30:14 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static bool	sle_ep(time_t time, t_philo *philo)
{
	time_t		start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (is_alive(philo) == IS_DEAD)
			return (IS_DEAD);
		usleep(100);
	}
	return (IS_ALIVE);
}

time_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	life_cycle_log(t_philo *philo, char *log)
{
	time_t	time_stamp;

	time_stamp = get_time() - philo->infos->start_time;
	printf("%-12ld %-4d %s\n", time_stamp, philo->id, log);
}

bool	dine_safely(t_philo *philo)
{
	life_cycle_log(philo, FORK);
	life_cycle_log(philo, FORK);
	life_cycle_log(philo, EAT);
	philo->last_meal = get_time();
	if (sle_ep(philo->infos->eat_time, philo) == IS_DEAD)
		return (IS_DEAD);
	return (TRUE);
}

void	life_cycle(t_philo *philo, t_infos *infos)
{
	int		meals;

	sem_unlink("forks");
	infos->all_forks = sem_open("forks", O_CREAT, infos->philo_num);
	if (infos->all_forks == SEM_FAILED)
	{
		str_error("SEMAPHORE OPEN ERROR");
		return ;
	}
	meals = infos->meals_num;
	if (!(philo->id % 2))
		sle_ep(philo->infos->eat_time, philo);
	while (meals == -1 || meals--)
	{
		if (dine_safely(philo) == IS_DEAD || meals == 0)
		{
			if (meals != FALSE)
				life_cycle_log(philo, DIED);
			break ;
		}
		life_cycle_log(philo, SLEEP);
		if (sle_ep(philo->infos->sleep_time, philo) == IS_ALIVE)
			life_cycle_log(philo, THINK);
	}
}
