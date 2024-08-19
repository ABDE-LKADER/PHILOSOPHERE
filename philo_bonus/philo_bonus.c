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

static void	*kill_childs(void *value)
{
	t_philo		*philo;

	philo = value;
	sem_wait(philo->infos->sem_dead);
	while (philo)
	{
		kill(philo->pid, SIGKILL);
		philo = philo->next;
	}
	return (NULL);
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
	if (pthread_create(&infos.kill, NULL, kill_childs, philo))
		return (error_cleaner(philo, CREATE_FAIL), EXIT_FAILURE);
	return (cleanup(philo, &infos), EXIT_SUCCESS);
}
