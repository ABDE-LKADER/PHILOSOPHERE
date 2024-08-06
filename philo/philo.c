/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/06 15:22:37 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	_sleep(time_t time)
{
	time_t		start;

	start  = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	*life_cycle(void *value)
{
	t_philo		*philo;

	philo = value;
	if (philo->tid % 2)
		_sleep(philo->infos->eat_time);
	while (TRUE)
	{
		pthread_mutex_lock(&philo->my_fork);
		life_cycle_log(philo, N1);
		pthread_mutex_lock(&philo->next->my_fork);
		life_cycle_log(philo, N1);
		life_cycle_log(philo, N2);
		philo->last_meal = get_time();
		_sleep(philo->infos->eat_time);
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_unlock(&philo->next->my_fork);
		life_cycle_log(philo, N3);
		_sleep(philo->infos->sleep_time);
		life_cycle_log(philo, N4);
	}
	return (philo);
}

int	threads_manager(t_philo *philo, t_infos *infos)
{
	t_philo				*loop;
	pthread_mutex_t		main_lock;

	loop = philo;
	pthread_mutex_init(&main_lock, NULL);
	while (philo)
	{
		if (get_time() - philo->last_meal >= infos->die_time)
		{
			pthread_mutex_lock(&main_lock);
			infos->philo_dead = TRUE;
			pthread_mutex_unlock(&main_lock);
			life_cycle_log(philo, N5);
			break ;
		}
		philo = philo->next;
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
