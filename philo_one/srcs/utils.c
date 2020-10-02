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

void		write_status_philo(t_philo *philo, char *action)
{
	long int		current_millisecond;

	if (*philo->is_die)
		return ;
	current_millisecond = get_current_millisecond() -
										philo->table->start_simulation;
	ft_putnbr_fd(current_millisecond, 1);
	ft_putstr_fd(" ms: ", 1);
	ft_putnbr_fd(philo->id + 1, 1);
	ft_putendl_fd(action, 1);
}

int			right_fork(int philo_id, int number_of_philo)
{
	return ((philo_id + 1) % number_of_philo);
}

void		*check_death(void *thread_data)
{
	t_philo		*philo;

	philo = (t_philo*)thread_data;
	while (get_current_millisecond() - philo->last_lunch_time
												<= philo->table->time_to_die)
		;
	pthread_mutex_lock(philo->table->mutex);
	write_status_philo(philo, " philosopher is died...");
	*philo->is_die = 1;
	pthread_mutex_unlock(philo->table->mutex);
	return (NULL);
}
