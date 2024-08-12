/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:31:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/12 21:54:11 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	cleanup(t_philo *philo, t_infos *infos)
{
	while (philo)
	{
		if (philo->id == infos->philo_num)
		{
			free(philo);
			break ;
		}
		free(philo);
		philo = philo->next;
	}
}

static int	create_philo_node(t_philo **philo, t_infos *infos, int id)
{
	t_philo		*new;
	t_philo		*last;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (str_error(ALLOC_FAIL), ERROR);
	(TRUE) && (new->id = id, new->infos = infos,
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
	int			id;
	t_philo		*loop;

	id = 0;
	while (++id <= infos->philo_num)
	{
		if (create_philo_node(philo, infos, id) == ERROR)
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
		if (philo->id == infos->philo_num)
			return (TRUE);
		philo = philo->next;
	}
	return (TRUE);
}
