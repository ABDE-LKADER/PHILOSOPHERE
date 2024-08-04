/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:30:51 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/04 18:52:46 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define N1 1
# define N2 2
# define N3 3
# define N4 4
# define N5 5
# define N6 6

# define TEN 10
# define NINE 57
# define ZERO 48

# define MTM 60
# define MPH 200
# define TIM 1000

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# define ERROR_MSG "\033[1;31mError:\033[0m <use a valid values>\n"
# define FAILED_MSG "\033[1;31mError:\033[0m <use a valid values>\n"
# define USAGE_MSG "\033[1;33mUsage:\033[0m <philo_num> <die_time> <eat_time> \
<sleep_time>\n"

typedef struct s_infos
{
	int				eat_time;
	int				die_time;
	int				philo_num;
	int				meals_num;
	int				sleep_time;
	int				start_time;
	bool			philo_dead;
	pthread_mutex_t	print_lock;
}					t_infos;

typedef struct s_philo
{
	int				uid;
	t_infos			*infos;
	pthread_t		my_thread;
	pthread_mutex_t	my_fork;
	struct s_philo	*next;
}					t_philo;

size_t		get_time(void);
int			_atoi(char *str);
void		*life_cycle(void *value);
void		putstr_fd(char *s, int fd);
void		print_use_mutex(t_philo *philo, int mode);
int			parcer(int ac, char **av, t_infos *infos);
t_philo		*init_philos(t_philo **philo, t_infos *infos);

#endif
