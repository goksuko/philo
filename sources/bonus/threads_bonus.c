/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 18:21:35 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/11 10:19:06 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	one_philo(t_philo *philo)
{
	print_status(philo, FORK);
	mutex_treasure_lock(philo->dead_lock);
	philo->table->dead_flag = philo->index + 1;
	mutex_treasure_unlock(philo->dead_lock);
	ft_usleep(philo->table->die_time);
	print_status(philo, DIED);
	return ;
}

void	*philos_thread(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->table->no_of_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		if (!eat_sleep_think(philo))
			break ;
		if (to_finish(philo->table))
			break ;
	}
	return (NULL);
}

void	threads_init(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &philos_thread,
				&table->philos[i]))
			ft_exit_perror(ERROR_THREAD, "Philo threads creation");
		ft_usleep(1);
		i++;
	}
	return ;
}
