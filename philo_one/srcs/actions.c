/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:40:02 by imicah            #+#    #+#             */
/*   Updated: 2020/10/02 12:40:03 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

//void	eating(t_philo *philo)
//{
//	const t_table	*table = philo->table;
//	const int 		id_right_fork = right_fork(philo->id, table->number_of_philo);
//
//	pthread_mutex_lock(philo->table->waiter);
//	pthread_mutex_lock(&table->forks_mutex[philo->id]);
//	write_status_philo(philo, " has taken a fork");
//	pthread_mutex_lock(&table->forks_mutex[id_right_fork]);
//	write_status_philo(philo, " has taken a fork");
//	pthread_mutex_unlock(philo->table->waiter);
//
//	write_status_philo(philo, " is eating");
//	philo->last_lunch_time = get_current_millisecond();
//	usleep((useconds_t)philo->table->time_to_eat);
//
//	pthread_mutex_unlock(&table->forks_mutex[philo->id]);
//	pthread_mutex_unlock(&table->forks_mutex[id_right_fork]);
//}

void	eating(t_philo *philo)
{
	const t_table	*table = philo->table;
	const int 		id_right_fork = right_fork(philo->id, table->number_of_philo);

	if (philo->id % 2)
	{
		pthread_mutex_lock(&table->forks_mutex[philo->id]);
		write_status_philo(philo, " has taken a fork");
		pthread_mutex_lock(&table->forks_mutex[id_right_fork]);
		write_status_philo(philo, " has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&table->forks_mutex[id_right_fork]);
		write_status_philo(philo, " has taken a fork");
		pthread_mutex_lock(&table->forks_mutex[philo->id]);
		write_status_philo(philo, " has taken a fork");
	}
	write_status_philo(philo, " is eating");
	philo->last_lunch_time = get_current_millisecond();
	usleep((useconds_t)philo->table->time_to_eat);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&table->forks_mutex[philo->id]);
		pthread_mutex_unlock(&table->forks_mutex[id_right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&table->forks_mutex[id_right_fork]);
		pthread_mutex_unlock(&table->forks_mutex[philo->id]);
	}
}

void	sleeping(t_philo *philo)
{
	write_status_philo(philo, " is sleeping");
	usleep((useconds_t)philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	write_status_philo(philo, " is thinking");
}

void	*action(void *thread_data)
{
	t_philo		*philo;
	pthread_t	thread;

	pthread_create(&thread, NULL, check_death, thread_data);
	philo = (t_philo*)thread_data;
	while (philo->number_of_times_philo_must_eat)
	{
		if (*philo->is_die)
			break ;
		eating(philo);
		if (*philo->is_die)
			break ;
		sleeping(philo);
		if (*philo->is_die)
			break ;
		thinking(philo);
		philo->number_of_times_philo_must_eat--;
	}
	pthread_join(thread, NULL);
	return (NULL);
}
