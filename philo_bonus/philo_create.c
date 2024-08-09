/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:31:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/08 21:55:07 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	cleanup(t_philo *philo, t_infos *infos)
{
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

void	join_threads(t_philo *philo, int max_id)
{
	while (philo)
	{
		if (pthread_join(philo->thread_id, NULL))
			str_error(JOIN_FAIL);
		if (philo->tid == max_id)
			break ;
		philo = philo->next;
	}
}

static int	create_philo_node(t_philo **philo, t_infos *infos, int tid)
{
	t_philo		*new;
	t_philo		*last;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (str_error(ALLOC_FAIL), ERROR);
	if (pthread_mutex_init(&new->meal_lock, NULL))
		return (str_error(INIT_FAIL), ERROR);
	if (pthread_mutex_init(&new->philo_fork, NULL))
	{
		if (pthread_mutex_destroy(&new->meal_lock))
			return (str_error(DESTROY_FAIL), ERROR);
		return (str_error(INIT_FAIL), ERROR);
	}
	(TRUE) && (new->tid = tid, new->infos = infos,
		new->next = NULL);
	if (!*philo)
		return (*philo = new, TRUE);
	last = *philo;
	while (last->next)
		last = last->next;
	last->next = new;
	return (TRUE);
}

int	init_philos(t_philo **philo, t_infos *infos)
{
	int			tid;
	t_philo		*loop;

	tid = 0;
	if (pthread_mutex_init(&infos->print_lock, NULL))
		return (str_error(INIT_FAIL), ERROR);
	if (pthread_mutex_init(&infos->dead_lock, NULL))
		return (str_error(INIT_FAIL), ERROR);
	while (++tid <= infos->philo_num)
	{
		if (create_philo_node(philo, infos, tid) == ERROR)
			return (ERROR);
	}
	loop = *philo;
	while (loop && loop->next)
		loop = loop->next;
	if (loop)
		loop->next = *philo;
	return (TRUE);
}

int	create_philos(t_philo *philos, t_infos *infos)
{
	t_philo		*philo;

	philo = philos;
	infos->start_time = get_time();
	while (philo)
	{
		philo->last_meal = get_time();
		if (pthread_create(&philo->thread_id, NULL, life_cycle, philo))
		{
			safe_access(&infos->dead_lock, &infos->philo_dead, TRUE, WRITE);
			return (join_threads(philos, philo->tid - 1),
				str_error(CREATE_FAIL), ERROR);
		}
		if (philo->tid == infos->philo_num)
			return (TRUE);
		philo = philo->next;
	}
	return (TRUE);
}
