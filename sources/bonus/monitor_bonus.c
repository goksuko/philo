/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 15:11:59 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/11 10:34:07 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	*monitor(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	while (1)
	{
		if (to_finish(table))
			break ;
		i = 0;
		while (i < table->no_of_philos)
		{
			if (check_if_starving(&table->philos[i]))
				break ;
			i++;
		}
	}
	return (NULL);
}

void	monitor_init(t_table *table)
{
	if (pthread_create(&table->monitor_thread, NULL, &monitor, table))
	{
		free(table->philos);
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->meal_lock);
		pthread_mutex_destroy(&table->print_lock);
		sem_destroy(table->forks_semaphore);
		ft_exit_perror(ERROR_THREAD, "Monitor thread creation");
	}
	return ;
}
