/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/11 14:55:04 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	threads_manager(t_philo *philo, t_infos *infos)
{
	t_philo		*loop;
	time_t		last_meal;

	loop = philo;
	while (loop)
	{
		// last_meal = ;
		if (last_meal == ERROR)
			break ;
		if (get_time() - last_meal >= infos->die_time)
		{
			// infos->philo_dead
			life_cycle_log(loop, DIED, TRUE);
			break ;
		}
		else if (infos->philos_full == infos->philo_num)
			break ;
		loop = loop->next;
	}
	join_threads(philo, infos->philo_num);
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
	return (threads_manager(philo, &infos),
		cleanup(philo, &infos), EXIT_SUCCESS);
}
