/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:39:44 by imicah            #+#    #+#             */
/*   Updated: 2020/10/02 12:39:45 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long int	get_current_millisecond(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);

}

void	write_status_philo(t_philo *philosopher, char *action)
{
	long int		current_millisecond;

	current_millisecond = get_current_millisecond() -
										philosopher->table->start_simulation;
	ft_putnbr_fd(current_millisecond, 1);
	ft_putstr_fd(" ms: ", 1);
	ft_putnbr_fd(philosopher->id + 1, 1);
	ft_putendl_fd(action, 1);
}

int 	left_fork(int philo_id, int number_of_philo)
{
	return ((philo_id - 1 + number_of_philo) % number_of_philo);
}

int 	right_fork(int philo_id, int number_of_philo)
{
	return ((philo_id + 1) % number_of_philo);
}

int 	check_time_to_die(t_philo *philo)
{
	if (get_current_millisecond() - philo->last_lunch_time
												>= philo->table->time_to_die)
	{
		philo->table->number_of_times_each_philo_must_eat = 0;
		write_status_philo(philo, " philosopher is died...");
		return (1);
	}
	return (0);
}
