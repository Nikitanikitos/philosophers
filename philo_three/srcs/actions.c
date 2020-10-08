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

#include "philo_three.h"

void	*check_death(void *thread_data)
{
	t_philo		*philo;

	philo = (t_philo*)thread_data;
	while (get_current_millisecond() - philo->last_lunch_time
												<= philo->table->time_to_die)
		usleep(10);
	sem_wait(philo->output_death);
	if (philo->number_of_times_philo_must_eat)
		write_status_philo(philo, " is died...\n");
	philo->died = 1;
	sem_post(philo->table->kill_childs);
	return (NULL);
}

void	eating(t_philo *philo)
{
	const t_table	*table = philo->table;

	sem_wait(table->sem_forks);
	write_status_philo(philo, " has taken a fork\n");
	sem_wait(table->sem_forks);
	write_status_philo(philo, " has taken a fork\n");
	write_status_philo(philo, " is eating\n");
	philo->last_lunch_time = get_current_millisecond();
	ft_usleep(philo->table->time_to_eat);
	sem_post(table->sem_forks);
	sem_post(table->sem_forks);
}

void	sleeping(t_philo *philo)
{
	write_status_philo(philo, " is sleeping\n");
	ft_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	write_status_philo(philo, " is thinking\n");
}

void	action(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, check_death, philo);
	while (philo->number_of_times_philo_must_eat)
	{
		if (philo->died)
			break ;
		eating(philo);
		if (philo->died)
			break ;
		sleeping(philo);
		if (philo->died)
			break ;
		thinking(philo);
		philo->number_of_times_philo_must_eat--;
	}
	pthread_join(thread, NULL);
}
