/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:31:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/06 15:18:48 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, N1);
}

int	_atoi(char *str)
{
	time_t		num;

	num = FALSE;
	(*str == '+') && (str++);
	while (*str && (*str >= ZERO && *str <= NINE))
	{
		num = num * TEN + *str - ZERO;
		if (num > INT_MAX)
			return (ERROR);
		str++;
	}
	return (num);
}

void	life_cycle_log(t_philo *philo, int mode)
{
	time_t		time;

	pthread_mutex_lock(&philo->infos->print_lock);
	time = get_time() - philo->infos->start_time;
	if (mode == N1 && !philo->infos->philo_dead)
		printf("%-12ld %-4d %s\n", time, philo->tid, FORK);
	if (mode == N2 && !philo->infos->philo_dead)
		printf("%-12ld %-4d %s\n", time, philo->tid, EAT);
	if (mode == N3 && !philo->infos->philo_dead)
		printf("%-12ld %-4d %s\n", time, philo->tid, SLEEP);
	if (mode == N4 && !philo->infos->philo_dead)
		printf("%-12ld %-4d %s\n", time, philo->tid, THINK);
	if (mode == N5 && philo->infos->philo_dead)
		printf("%-12ld %-4d %s\n", time, philo->tid, DIED);
	pthread_mutex_unlock(&philo->infos->print_lock);
}
