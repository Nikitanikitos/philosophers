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

#include "philo_two.h"

void	eating(t_philo *philo)
{
	const t_table	*table = philo->table;
	int				id_right_fork;

	id_right_fork = right_fork(philo->id, table->number_of_philo);
	if (philo->id % 2)
		take_two_forks(philo, philo->id, id_right_fork);
	else
		take_two_forks(philo, id_right_fork, philo->id);
	write_status_philo(philo, " is eating\n");
	philo->last_lunch_time = get_current_millisecond();
	ft_usleep(philo->table->time_to_eat / 1000);
	if (philo->id % 2)
		put_two_forks(philo, id_right_fork, philo->id);
	else
		put_two_forks(philo, philo->id, id_right_fork);
}

void	sleeping(t_philo *philo)
{
	write_status_philo(philo, " is sleeping\n");
	ft_usleep(philo->table->time_to_sleep / 1000);
}

void	thinking(t_philo *philo)
{
	write_status_philo(philo, " is thinking\n");
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
