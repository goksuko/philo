/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_philo_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 00:45:07 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/06/27 19:51:49 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	do_the_job(t_philo *philo)
{
	print_status(philo, EATING);
	mutex_treasure_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->has_eaten++;
	mutex_treasure_unlock(&philo->table->meal_lock);
	ft_usleep(philo->table->eat_time);
	leave_forks(philo);
	print_status(philo, SLEEPING);
	ft_usleep(philo->table->sleep_time);
	print_status(philo, THINKING);
	ft_usleep(1);
	return ;
}

bool	eat_sleep_think(t_philo *philo)
{
	while (1)
	{
		if (take_forks(philo))
			break ;
		if (to_finish(philo->table))
			break ;
	}
	do_the_job(philo);
	if (to_finish(philo->table))
		return (false);
	return (true);
}
