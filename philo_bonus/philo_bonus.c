/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 21:44:51 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_alive(t_philo *philo)
{
	if (get_time() - philo->last_meal >= philo->infos->die_time)
		return (IS_DEAD);
	return (IS_ALIVE);
}

static void	*meals_childs(void *value)
{
	t_infos		*infos;

	infos = value;
	while (waitpid(-1, NULL, 0) != -1)
		;
	sem_post(infos->sem_dead);
}

static void	kill_childs(t_philo *philo, t_infos *infos)
{
	t_philo		*head;

	head = philo;
	sem_wait(infos->sem_dead);
	while (philo)
	{
		kill(philo->pid, SIGKILL);
		philo = philo->next;
	}
	pthread_join(infos->kill, NULL);
	cleanup(head, infos);
}

int	main(int ac, char **av)
{
	t_infos		infos;
	t_philo		*philo;

	philo = NULL;
	memset(&infos, false, sizeof(t_infos));
	if (ac != 5 && ac != 6)
		return (str_error(USAGE_MSG), EXIT_FAILURE);
	if (parcer(ac, av, &infos) == ERROR)
		return (str_error(ERROR_MSG), EXIT_FAILURE);
	if (init_philos(&philo, &infos) == ERROR)
		return (cleanup(philo, &infos), EXIT_FAILURE);
	if (create_philos(philo, &infos) == ERROR)
		return (cleanup(philo, &infos), EXIT_FAILURE);
	if (pthread_create(&infos.kill, NULL, meals_childs, &infos))
		return (error_cleaner(philo, CREATE_FAIL), EXIT_FAILURE);
	return (kill_childs(philo, &infos), EXIT_SUCCESS);
}
