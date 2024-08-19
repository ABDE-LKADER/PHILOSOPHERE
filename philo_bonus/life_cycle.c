/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:19:32 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 21:47:13 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void life_cycle_log(t_philo *philo, char *log)
{
	time_t time_stamp;

	sem_wait(philo->infos->sem_log);
	time_stamp = get_time() - philo->infos->start_time;
	printf("%-12ld %-4d %s\n", time_stamp, philo->id, log);
	sem_post(philo->infos->sem_log);
}

static void urgent_death_detect(t_philo *philo, t_infos *infos)
{
	time_t time_stamp;

	sem_wait(infos->sem_log);
	time_stamp = get_time() - philo->infos->start_time;
	printf("%-12ld %-4d %s\n", time_stamp, philo->id, DIED);
	sem_post(infos->sem_dead);
	exit(EXIT_SUCCESS);
}

static void *is_dead(void *value)
{
	t_philo *philo;

	philo = value;
	while (true)
	{
		sem_wait(philo->sem_mute);
		if (is_alive(philo) == IS_DEAD)
			urgent_death_detect(philo, philo->infos);
		sem_post(philo->sem_mute);
	}
	return (NULL);
}

static void dine_safely(t_philo *philo, t_infos *infos)
{
	sem_wait(infos->philo_forks);
	life_cycle_log(philo, FORK);
	if (infos->philo_num == 1)
	{
		sle_ep(infos->die_time);
		return ;
	}
	sem_wait(infos->philo_forks);
	life_cycle_log(philo, FORK);
	life_cycle_log(philo, EAT);
	sem_wait(philo->sem_mute);
	philo->last_meal = get_time();
	sem_post(philo->sem_mute);
	sle_ep(infos->eat_time);
	sem_post(infos->philo_forks);
	sem_post(infos->philo_forks);
}

void life_cycle(t_philo *philo, t_infos *infos)
{
	pthread_t 	tid;
	char		*name;

	name = num_toa(philo->id);
	if (name == NULL)
		sem_post(infos->sem_dead);
	philo->last_meal = get_time();
	philo->sem_mute = create_sem(name, 1, TRUE);
	if (philo->sem_mute == SEM_FAILED)
		return;
	if (pthread_create(&tid, NULL, is_dead, philo))
		return ((void)sem_post(infos->sem_dead));
	pthread_detach(tid);
	while (infos->meals_num == -1 || infos->meals_num--)
	{
		dine_safely(philo, infos);
		if (infos->meals_num == 0)
			exit(EXIT_SUCCESS);
		life_cycle_log(philo, SLEEP);
		sle_ep(philo->infos->sleep_time);
		life_cycle_log(philo, THINK);
	}
}
