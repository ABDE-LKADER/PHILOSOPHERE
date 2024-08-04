/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:31:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/04 16:48:05 by abadouab         ###   ########.fr       */
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

void	print_use_mutex(t_philo *philo, int mode)
{
	int		time;

	pthread_mutex_lock(&philo->infos->print_lock);
	if (!philo->infos->philo_dead)
	{
		time = get_time() - philo->infos->start_time;
		if (mode == N1)
			printf("%-12d %-4d %s\n", time, philo->uid, FORK);
		if (mode == N2)
			printf("%-12d %-4d %s\n", time, philo->uid, EAT);
		if (mode == N3)
			printf("%-12d %-4d %s\n", time, philo->uid, SLEEP);
		if (mode == N4)
			printf("%-12d %-4d %s\n", time, philo->uid, THINK);
	}
	if (philo->infos->philo_dead && mode == N5)
		printf("%-12d %-4d %s\n", time, philo->uid, DIE);
	pthread_mutex_unlock(&philo->infos->print_lock);
}

int	_atoi(char *str)
{
	long		num;

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
