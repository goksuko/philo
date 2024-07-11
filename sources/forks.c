/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 11:20:50 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/11 10:47:05 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	forks_init(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->no_of_philos)
	{
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % table->no_of_philos];
		i++;
	}
	table->forks = philos[0].left_fork;
	return ;
}

bool	left_fork(t_philo *philo)
{
	mutex_treasure_lock(philo->left_fork);
	print_status(philo, FORK);
	return (true);
}

bool	right_fork(t_philo *philo)
{
	mutex_treasure_lock(philo->right_fork);
	print_status(philo, FORK);
	return (true);
}
