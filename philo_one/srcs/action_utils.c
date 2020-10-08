/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:11:28 by imicah            #+#    #+#             */
/*   Updated: 2020/04/30 23:01:51 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_two_forks(t_philo *philo, int id_fork1, int id_fork2)
{
	const t_table	*table = philo->table;

	pthread_mutex_lock(&table->forks_mutex[id_fork1]);
	write_status_philo(philo, " has taken a fork\n");
	pthread_mutex_lock(&table->forks_mutex[id_fork2]);
	write_status_philo(philo, " has taken a fork\n");
}

void	put_two_forks(t_philo *philo, int id_fork1, int id_fork2)
{
	const t_table	*table = philo->table;

	pthread_mutex_unlock(&table->forks_mutex[id_fork1]);
	pthread_mutex_unlock(&table->forks_mutex[id_fork2]);
}

void	*check_death(void *thread_data)
{
	t_philo				*philo;

	philo = (t_philo*)thread_data;
	while (get_current_millisecond() - philo->last_lunch_time
												<= philo->table->time_to_die)
		usleep(10);
	if (philo->number_of_times_philo_must_eat)
	{
		pthread_mutex_lock(philo->table->mutex);
		write_status_philo(philo, " is died...\n");
		*philo->is_die = 1;
		pthread_mutex_unlock(philo->table->mutex);
	}
	return (NULL);
}
