/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:31:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/16 07:38:25 by abadouab         ###   ########.fr       */
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
	int		id;

	id = 0;
	while (++id <= infos->philo_num)
	{
		if (create_philo_node(philo, infos, id) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

int	create_philos(t_philo *philo, t_infos *infos)
{
	infos->start_time = get_time();
	while (philo)
	{
		philo->pid = fork();
		if (philo->pid == ERROR)
			return (ERROR);
		if (philo->pid == 0)
		{
			life_cycle(philo, infos);
			break ;
		}
		philo = philo->next;
	}
	return (TRUE);
}
