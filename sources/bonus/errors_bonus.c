/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 22:55:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/05 13:15:44 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

char	*ft_error(t_error code)
{
	static char	*str[] = {[NO_ERROR] = "No Error",
	[ERROR_ARGUMENT_COUNT] = "Invalid Amount of Arguments",
	[ERROR_INVALID_ARGUMENTS] = "Arguments can only be valid numbers",
	[ERROR_INVALID_PHILOS] = "Invalid Number of Philosophers",
	[ERROR_INVALID_die_time] = "Invalid Time to Die",
	[ERROR_INVALID_eat_time] = "Invalid Time to Eat",
	[ERROR_INVALID_sleep_time] = "Invalid Time to Sleep",
	[ERROR_THREAD] = "Thread Creation Failure",
	[ERROR_JOIN] = "Thread Join Failure",
	[ERROR_ALLOCATION] = "Allocation Failure",
	[ERROR_INPUT] = "Invalid Number",
	[ERROR_MUTEX_INIT] = "Mutex Initialization Failure",
	[ERROR_MUTEX_LOCK] = "Mutex Lock Failure",
	[ERROR_MUTEX_UNLOCK] = "Mutex Unlock Failure",
	[ERROR_USLEEP] = "usleep Failure",
	[ERROR_SEMAPHORE] = "Semaphore Failure",
	[UNDEFINED_ERROR] = "Undefined Error"};

	if (code < 0 || code >= UNDEFINED_ERROR)
		return (str[UNDEFINED_ERROR]);
	else
		return (str[code]);
}

int	ft_print_error(t_error code)
{
	printf("%s\n", ft_error(code));
	return (code);
}

bool	check_argument_problem(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == '-')
			j++;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (true);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60
		|| (argv[5] && ft_atoi(argv[5]) < 1))
		return (true);
	return (false);
}

bool	check_argument_count_problem(int argc)
{
	if (argc != 5 && argc != 6)
		return (true);
	return (false);
}

void	ft_exit_perror(t_error code, char *s)
{
	perror(s);
	exit(code);
}
