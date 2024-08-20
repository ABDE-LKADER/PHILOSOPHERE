/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:30:51 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 21:16:49 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
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
# define USAGE_MSG "\033[1;33mUsage:\033[0m <philo_num> <die_time> <eat_time> \
<sleep_time>"

# define SEM_OPEN "\033[1;31mError:\033[0m <failed to open the semaphore>"
# define CREATE_FAIL "\033[1;31mError:\033[0m <failed to create a new thread>"
# define DETACH_FAIL "\033[1;31mError:\033[0m <failed to detach the thread>"
# define ALLOC_FAIL "\033[1;31mError:\033[0m <failed to allocate memory>"

typedef struct s_infos
{
	pthread_t		kill;
	sem_t			*sem_log;
	sem_t			*sem_dead;
	sem_t			*philo_forks;
	int				philo_num;
	int				meals_num;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	time_t			start_time;
}					t_infos;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	t_infos			*infos;
	sem_t			*sem_mute;
	time_t			last_meal;
	struct s_philo	*next;
}					t_philo;

time_t		get_time(void);
char		*num_toa(int n);
void		str_error(char *s);
void 		sle_ep(time_t time);
bool		is_alive(t_philo *philo);
void		cleanup(t_philo *philo, t_infos *infos);
void		error_cleaner(t_philo *philo, char *msg);
int			parcer(int ac, char **av, t_infos *infos);
void		life_cycle(t_philo *philo, t_infos *infos);
sem_t		*create_sem(char *name, int num, bool mode);
int			init_philos(t_philo **philo, t_infos *infos);
int			create_philos(t_philo *philo, t_infos *infos);

#endif
