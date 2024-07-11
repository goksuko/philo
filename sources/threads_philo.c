/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_philo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 00:45:07 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/04 13:26:30 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	do_the_job(t_philo *philo)
{
	mutex_treasure_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->has_eaten++;
	mutex_treasure_unlock(&philo->table->meal_lock);
	print_status(philo, EATING);
	ft_usleep(philo->table->eat_time);
	mutex_treasure_unlock(philo->right_fork);
	mutex_treasure_unlock(philo->left_fork);
	print_status(philo, SLEEPING);
	ft_usleep(philo->table->sleep_time);
	print_status(philo, THINKING);
	ft_usleep(1);
	return ;
}

bool	even_philo(t_philo *philo)
{
	while (1)
	{
		if (left_fork(philo))
			break ;
	}
	if (right_fork(philo))
	{
		do_the_job(philo);
		return (true);
	}
	else
		mutex_treasure_unlock(philo->left_fork);
	return (false);
}

bool	odd_philo(t_philo *philo)
{
	while (1)
	{
		if (right_fork(philo))
			break ;
	}
	if (left_fork(philo))
	{
		do_the_job(philo);
		return (true);
	}
	else
		mutex_treasure_unlock(philo->right_fork);
	return (false);
}

bool	eat_sleep_think(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		if (!even_philo(philo))
			return (false);
	}
	else
	{
		if (!odd_philo(philo))
			return (false);
	}
	return (true);
}
