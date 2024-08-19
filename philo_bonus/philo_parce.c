/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:10:42 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 19:27:27 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	str_error(char *s)
{
	if (!s)
		return ;
	while (*s)
		write(2, s++, 1);
	write(2, "\n", 1);
}

static int	ato_num(char *str)
{
	time_t		num;

	num = 0;
	(*str == '+') && (str++);
	while (*str && (*str >= 48 && *str <= 57))
	{
		num = num * 10 + *str - 48;
		if (num > INT_MAX)
			return (ERROR);
		str++;
	}
	return (num);
}

int	parcer(int ac, char **av, t_infos *infos)
{
	int		num;
	int		index;

	infos->meals_num = -1;
	while (--ac)
	{
		(TRUE) && (index = ERROR, num = ato_num(av[ac]));
		while (av[ac][++index])
		{
			if (!index && av[ac][index] == '+')
				av[ac]++;
			if (!(av[ac][index] >= 48 && av[ac][index] <= 57))
				return (ERROR);
		}
		if (!*av[ac] || (num > 200 && ac == 1))
			return (ERROR);
		if (num < 60 && (ac == 2 || ac == 3 || ac == 4))
			return (ERROR);
		(ac == 1) && (infos->philo_num = num);
		(ac == 2) && (infos->die_time = num);
		(ac == 3) && (infos->eat_time = num);
		(ac == 4) && (infos->sleep_time = num);
		(ac == 5) && (infos->meals_num = num);
	}
	return (TRUE);
}
