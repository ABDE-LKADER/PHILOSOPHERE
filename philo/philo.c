/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:29:27 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/01 20:03:56 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	_atoi(char *str)
{
	long		num;

	num = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		num = num * 10 + *str - 48;
		if (num > 2147483647)
			return (ERROR);
		str++;
	}
	return (num);
}

int	parcer(int ac, char **av, t_infos *infos)
{
	int		num;
	int		index;

	infos->number_of_times = ERROR;
	while (--ac)
	{
		(index = -1, num = _atoi(av[ac]));
		while (av[ac][++index])
		{
			if (!index && av[ac][index] == '+')
				av[ac]++;
			if (!(av[ac][index] >= '0' && av[ac][index] <= '9'))
				return (ERROR);
		}
		if (num > 200 && ac == 1)
			return (ERROR);
		if (num < 60 && (ac == 2 || ac == 3 || ac == 4))
			return (ERROR);
		(ac == 1) && (infos->number_of_philos = num);
		(ac == 2) && (infos->time_to_die = num);
		(ac == 3) && (infos->time_to_eat = num);
		(ac == 4) && (infos->time_to_sleep = num);
		(ac == 5) && (infos->number_of_times = num);
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	int			mode;
	t_infos		infos;

	if (ac != 5 && ac != 6)
		return (write(STDERR_FILENO, USAGE_MSG, 68), EXIT_FAILURE);
	memset(&infos, false, sizeof(infos));
	if (parcer(ac, av, &infos) == ERROR)
		return (write(STDERR_FILENO, ERROR_MSG, 39), EXIT_FAILURE);
	mode = FALSE;
	(infos.number_of_times != ERROR) && (mode = TRUE);
	printf("NUMBER: %d EAT: %d DIE: %d SLEEP: %d\n", infos.number_of_philos,
		infos.time_to_eat, infos.time_to_die, infos.time_to_sleep);
	while (infos.number_of_times == ERROR || infos.number_of_times)
	{
		printf("LOOPING\n");
		(mode) && (infos.number_of_times--);
	}
	return (EXIT_SUCCESS);	
}
