/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 00:32:32 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/11 10:36:46 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_EAT 250

typedef enum e_action
{
	THINKING,
	DIED,
	SLEEPING,
	EATING,
	FORK,
}					t_action;

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGUMENT_COUNT,
	ERROR_INVALID_ARGUMENTS,
	ERROR_INVALID_PHILOS,
	ERROR_INVALID_die_time,
	ERROR_INVALID_eat_time,
	ERROR_INVALID_sleep_time,
	ERROR_THREAD,
	ERROR_JOIN,
	ERROR_ALLOCATION,
	ERROR_INPUT,
	ERROR_MUTEX_INIT,
	ERROR_MUTEX_LOCK,
	ERROR_MUTEX_UNLOCK,
	ERROR_USLEEP,
	UNDEFINED_ERROR,
}					t_error;

// print lock: in order to not to write at the same time
// dead lock: in order to not to change the dead flag at the same time
// meal lock: in order to not to change and check the meal_eaten number

typedef struct s_philo
{
	struct s_table	*table;
	int				*dead_flag;
	int				*full_flag;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
	int				index;
	pthread_t		thread;
	int				has_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				status;
}					t_philo;

typedef struct s_table
{
	t_philo			*philos;
	pthread_t		monitor_thread;
	pthread_mutex_t	*forks;
	int				dead_flag;
	int				full_flag;
	int				finish_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	int				no_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				no_of_eat;
	long long		start_time;
}					t_table;

// table.c

void				table_init(t_table *table, int argc, char **argv);

// philos.c

void				philos_init(t_table *table);

// check.c

int					check_if_died(t_table *table);
int					check_if_full(t_table *table);
int					to_finish(t_table *table);
bool				check_if_starving(t_philo *philo);
void				hoist_flag(t_table *table);

// clean.c

void				clean_all(t_table *table);

// monitor.c

void				monitor_init(t_table *table);

// errors.c

char				*ft_error(t_error code);
int					ft_print_error(t_error code);
bool				check_argument_count_problem(int argc);
bool				check_argument_problem(int argc, char **argv);
void				ft_exit_perror(t_error code, char *s);

// print.c

void				print_status(t_philo *philo, t_action status);
int					ft_usleep(size_t milliseconds);
long long			get_current_time(void);
void				print_dead(t_philo *philo, t_action status);

// threads.c

void				threads_init(t_table *table, t_philo *philos);

// threads_philo.c

bool				eat_sleep_think(t_philo *philo);

// forks.c

void				forks_init(t_table *table, t_philo *philos);
bool				left_fork(t_philo *philo);
bool				right_fork(t_philo *philo);

// main.c

void				join_threads(t_table *table);

// ft_atoi.c

int					ft_atoi(const char *nptr);

// ft_calloc.c

void				*ft_calloc(size_t nmemb, size_t size);

// locks.c

void				mutex_treasure_lock(pthread_mutex_t *mutex);
void				mutex_treasure_unlock(pthread_mutex_t *mutex);

#endif
