/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/03 15:05:37 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/11 10:45:15 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	table_init(t_table *table, int argc, char **argv);
void	table_init_continue1(t_table *table);
void	table_init_continue2(t_table *table);

void	table_init(t_table *table, int argc, char **argv)
{
	table->dead_flag = 0;
	table->full_flag = 0;
	table->finish_flag = 0;
	table->no_of_philos = ft_atoi(argv[1]);
	table->die_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	table->start_time = get_current_time();
	ft_usleep(2);
	if (argc == 6)
		table->no_of_eat = ft_atoi(argv[5]);
	else
		table->no_of_eat = MAX_EAT;
	table->philos = (t_philo *)ft_calloc(sizeof(t_philo), table->no_of_philos);
	if (errno == ENOMEM || !table->philos)
		ft_exit_perror(ERROR_ALLOCATION, "Philos in Table Init");
	table_init_continue1(table);
	table_init_continue2(table);
	return ;
}

void	table_init_continue1(t_table *table)
{
	if (pthread_mutex_init(&table->dead_lock, NULL) < 0)
	{
		free(table->philos);
		ft_exit_perror(ERROR_MUTEX_INIT, "Dead Lock in Table Init");
	}
	if (pthread_mutex_init(&table->meal_lock, NULL) < 0)
	{
		free(table->philos);
		pthread_mutex_destroy(&table->dead_lock);
		ft_exit_perror(ERROR_MUTEX_INIT, "Meal Lock in Table Init");
	}
	if (pthread_mutex_init(&table->print_lock, NULL) < 0)
	{
		free(table->philos);
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->meal_lock);
		ft_exit_perror(ERROR_MUTEX_INIT, "Print Lock in Table Init");
	}
	return ;
}

void	table_init_continue2(t_table *table)
{
	table->forks_semaphore = (sem_t *)ft_calloc(sizeof(sem_t), 1);
	if (errno == ENOMEM || !table->forks_semaphore)
	{
		free(table->philos);
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->meal_lock);
		pthread_mutex_destroy(&table->print_lock);
		ft_exit_perror(ERROR_ALLOCATION, "Forks Semaphore in Table Init");
	}
	if (sem_init(table->forks_semaphore, 0, table->no_of_philos) < 0)
	{
		free(table->philos);
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->meal_lock);
		pthread_mutex_destroy(&table->print_lock);
		ft_exit_perror(ERROR_SEMAPHORE, "Forks Semaphore in Table Init");
	}
	return ;
}
