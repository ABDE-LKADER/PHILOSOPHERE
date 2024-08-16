/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:30:51 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/16 11:30:10 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define READ 0
# define WRITE 1
# define INCR 2

# define LOCK 0
# define UNLOCK 1

# define IS_DEAD 0
# define IS_ALIVE 1

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

# define ERROR_MSG "\033[1;31mError:\033[0m <use a valid values>"
# define FAILED_MSG "\033[1;31mError:\033[0m <use a valid values>"
# define USAGE_MSG "\033[1;33mUsage:\033[0m <philo_num> <die_time> <eat_time> \
<sleep_time>"

# define JOIN_FAIL "\033[1;31mError:\033[0m <failed to join the thread>"
# define INIT_FAIL "\033[1;31mError:\033[0m <failed to initialize the mutex>"
# define LOCK_FAIL "\033[1;31mError:\033[0m <failed to lock the mutex>"
# define UNLOCK_FAIL "\033[1;31mError:\033[0m <failed to lock the mutex>"
# define CREATE_FAIL "\033[1;31mError:\033[0m <failed to create a new thread>"
# define ALLOC_FAIL "\033[1;31mError:\033[0m <failed to allocate memory>"

typedef struct s_infos
{
	int				philo_num;
	int				meals_num;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	long			philo_dead;
	long			philos_full;
	sem_t			all_forks;
	time_t			start_time;
}					t_infos;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	t_infos			*infos;
	time_t			last_meal;
	struct s_philo	*next;
}					t_philo;

time_t		get_time(void);
void		str_error(char *s);
bool		is_alive(t_philo *philo);
void		life_cycle_log(t_philo *philo, char *log);
int			parcer(int ac, char **av, t_infos *infos);
void		life_cycle(t_philo *philo, t_infos *infos);
int			init_philos(t_philo **philo, t_infos *infos);
void		cleanup(t_philo *philo, t_infos *infos);
int			create_philos(t_philo *philo, t_infos *infos);

#endif
