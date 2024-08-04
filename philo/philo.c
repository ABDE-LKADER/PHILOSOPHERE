/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/04 19:41:25 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*life_cycle(void *value)
{
	t_philo		*philo;

	philo = value;
	if (!(philo->uid % N2))
		usleep (philo->infos->eat_time * TIM);
	while (TRUE)
	{
		pthread_mutex_lock(&philo->my_fork);
		print_use_mutex(philo, N1);
		pthread_mutex_lock(&philo->next->my_fork);
		print_use_mutex(philo, N1);
		print_use_mutex(philo, N2);
		usleep(philo->infos->eat_time * TIM);
		print_use_mutex(philo, N3);
		usleep(philo->infos->sleep_time * TIM);
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_unlock(&philo->next->my_fork);
		print_use_mutex(philo, N4);
	}
	print_use_mutex(philo, N5);
	return (philo);
}

int	main(int ac, char **av)
{
	t_infos		infos;
	t_philo		*head;
	t_philo		*philo;

	(memset(&infos, false, sizeof(t_infos)), philo = NULL,
		pthread_mutex_init(&infos.print_lock, NULL));
	if (ac != N5 && ac != N6)
		return (putstr_fd(USAGE_MSG, STDERR_FILENO), EXIT_FAILURE);
	if (parcer(ac, av, &infos) == ERROR)
		return (putstr_fd(ERROR_MSG, STDERR_FILENO), EXIT_FAILURE);
	if (init_philos(&philo, &infos) == NULL)
		return (putstr_fd(FAILED_MSG, STDERR_FILENO), EXIT_FAILURE);
	head = philo;
	while (philo && !infos.philo_dead)
		philo = philo->next;
	return (EXIT_SUCCESS);
}
