/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   locks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 12:26:36 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/06/27 13:36:21 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	mutex_treasure_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		ft_exit_perror(ERROR_MUTEX_LOCK, "Mutex lock");
	return ;
}

void	mutex_treasure_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		ft_exit_perror(ERROR_MUTEX_UNLOCK, "Mutex unlock");
	return ;
}
