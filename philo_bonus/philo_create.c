/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:31:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/20 21:07:31 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

sem_t	*create_sem(char *name, int num, bool mode)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, num);
	if (sem == SEM_FAILED)
	{
		if (mode == TRUE)
			free(name);
		return (str_error(SEM_OPEN), SEM_FAILED);
	}
	sem_unlink(name);
	if (mode == TRUE)
		free(name);
	return (sem);
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
	if (infos->philo_num == 0 || infos->meals_num == 0)
		exit (EXIT_SUCCESS);
	infos->sem_log = create_sem("log", 1, FALSE);
	if (infos->sem_log == SEM_FAILED)
		return (ERROR);
	infos->sem_dead = create_sem("die", 0, FALSE);
	if (infos->sem_dead == SEM_FAILED)
		return (ERROR);
	infos->philo_forks = create_sem("forks", infos->philo_num, FALSE);
	if (infos->philo_forks == SEM_FAILED)
		return (ERROR);
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
