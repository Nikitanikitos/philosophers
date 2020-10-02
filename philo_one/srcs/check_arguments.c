#include "philo_one.h"

int 	exit_with_error(char *error)
{
	ft_putstr_fd("\e[31m", 2);
	ft_putendl_fd(error, 2);
	ft_putstr_fd("\e[31m", 5);
	return (1);
}

int		is_number(char *number)
{
	if (*number == '-' || *number == '+')
		number++;
	if (*number == '\0')
		return (0);
	while (*number)
		if (!ft_isdigit(*number++))
			return (0);
	return (1);
}

int 	check_that_is_number(char **av)
{
	int 	i;

	i = 1;
	while (av[i])
	{
		if (!is_number(av[i++]))
			return (FALSE);
	}
	return (TRUE);
}

int 	check_that_is_correct_number(char **av)
{
	int 	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i++]) < 0)
			return (FALSE);
	}
	return (TRUE);
}

int		check_arguments(int ac, char **av)
{
	if (ac < 5)
		return (exit_with_error("Not enough arguments"));
	else if (ac > 6)
		return (exit_with_error("Too many arguments"));
	else if (!check_that_is_number(av))
		return (exit_with_error("Arguments must be numbers"));
	else if (!check_that_is_correct_number(av))
		return (exit_with_error("Arguments must be at least zero"));
	return (0);
}
