/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/07 11:14:54 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	safe_read_write(pthread_mutex_t *mutex, int *value, int mode)
{
	(void)mode;
	pthread_mutex_lock(mutex);
	pthread_mutex_unlock(mutex);
	return (*value);
}

int	threads_manager(t_philo *philo, t_infos *infos)
{
	time_t				time;
	t_philo				*loop;

	loop = philo;
	while (philo)
	{
		pthread_mutex_lock(&philo->safe_check);
		time = philo->last_meal;
		pthread_mutex_unlock(&philo->safe_check);
		if (get_time() - time >= infos->die_time)
		{
			pthread_mutex_lock(&philo->infos->check_philo);
			infos->philo_dead = TRUE;
			pthread_mutex_unlock(&philo->infos->check_philo);
			life_cycle_log(philo, N5);
			break ;
		}
		philo = philo->next;
	}
	while (loop)
	{
		pthread_join(loop->my_thread, NULL);
		if (loop->tid == infos->philo_num)
			break ;
		loop = loop->next;
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_infos		infos;
	t_philo		*philo;

	(memset(&infos, false, sizeof(t_infos)), philo = NULL);
	if (ac != N5 && ac != N6)
		return (putstr_fd(USAGE_MSG, STDERR_FILENO), EXIT_FAILURE);
	if (parcer(ac, av, &infos) == ERROR)
		return (putstr_fd(ERROR_MSG, STDERR_FILENO), EXIT_FAILURE);
	if (init_philos(&philo, &infos) == NULL)
		return (putstr_fd(FAILED_MSG, STDERR_FILENO), EXIT_FAILURE);
	if (threads_manager(philo, &infos) == ERROR)
		return (putstr_fd(FAILED_MSG, STDERR_FILENO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
