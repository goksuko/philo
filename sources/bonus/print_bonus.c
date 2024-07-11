/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 18:29:30 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/11 10:32:46 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

char	*status_strs(t_action status)
{
	static char	*str[] = {[THINKING] = "is thinking", [DIED] = "died",
	[SLEEPING] = "is sleeping", [EATING] = "is eating",
	[FORK] = "has taken a fork"};

	return (str[status]);
}

// gettimeofday: gets the system's clock time
// the current time is expressed in elapsed seconds and microseconds
// since 00:00:00, January 1, 1970 (Unix Epoch)

// tv_sec is seconds
// tv_usec is microseconds
// dividing it by 1000 gives milliseconds.
// tv is timeval (with tv_sec and tv_usec)
// tz is timezone

// 1 sec = hundred thousand (100 000) microseconds
// 1 sec = thousand (1000) milliseconds

// 1000LL is a way of representing the number 1000 as a long long integer.
// This is often used in situations where you want to ensure that
// arithmetic involving this constant is performed using long long
// arithmetic, especially if overflow might be a concern.

long long	get_current_time(void)
{
	struct timeval	time;
	long long		result;

	if (gettimeofday(&time, NULL))
		return (EXIT_FAILURE);
	result = time.tv_sec * 1000LL + time.tv_usec / 1000LL;
	return (result);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (usleep(50))
			ft_exit_perror(ERROR_USLEEP, "in ft_usleep");
	}
	return (0);
}

void	print_status(t_philo *philo, t_action status)
{
	int	finish_flag;

	mutex_treasure_lock(philo->dead_lock);
	finish_flag = philo->table->finish_flag;
	mutex_treasure_unlock(philo->dead_lock);
	if (!finish_flag)
	{
		mutex_treasure_lock(philo->print_lock);
		printf("%lld %d %s\n", get_current_time(), philo->index + 1,
			status_strs(status));
		mutex_treasure_unlock(philo->print_lock);
	}
	if (status == DIED)
		hoist_flag(philo->table);
	return ;
}
