/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 11:20:50 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/05 13:23:50 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

bool	take_forks(t_philo *philo)
{
	if (to_finish(philo->table))
		return (false);
	if (sem_wait(philo->forks_semaphore) == 0)
	{
		if (sem_wait(philo->forks_semaphore) == 0)
		{
			print_status(philo, FORK);
			print_status(philo, FORK);
			return (true);
		}
		else
		{
			sem_post(philo->forks_semaphore);
			return (false);
		}
	}
	else
		return (false);
}

bool	leave_forks(t_philo *philo)
{
	sem_post(philo->forks_semaphore);
	sem_post(philo->forks_semaphore);
	return (true);
}
