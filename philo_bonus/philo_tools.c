/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:47:56 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 21:46:42 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	get_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*num_toa(int n)
{
	int				len;
	char			*snum;

	len = get_len(n);
	snum = malloc(len + 1 * sizeof(char));
	if (!snum)
		return (str_error(ALLOC_FAIL), NULL);
	snum[len] = '\0';
	while (len--)
	{
		snum[len] = n % 10 + '0';
		n /= 10;
	}
	return (snum);
}

void	error_cleaner(t_philo *philo, char *msg)
{
	t_philo		*head;
	t_infos		*infos;

	head = philo;
	infos = philo->infos;
	sem_wait(infos->sem_log);
	while (philo)
	{
		kill (philo->pid, SIGKILL);
		philo = philo->next;
	}
	str_error(msg);
	sem_post(infos->sem_log);
	cleanup(philo, infos);
}

void	cleanup(t_philo *philo, t_infos *infos)
{
	while (waitpid(-1, NULL, 0) != -1)
		;
	sem_post(infos->sem_dead);
	sem_close(infos->sem_log);
	sem_close(infos->sem_dead);
	sem_close(infos->philo_forks);
	pthread_join(infos->kill, NULL);
	while (philo)
	{
		sem_close(philo->sem_mute);
		free(philo);
		philo = philo->next;
	}
}
