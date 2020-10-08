/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:39:51 by imicah            #+#    #+#             */
/*   Updated: 2020/10/02 12:39:52 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	table_init(t_table *table, char **av, pthread_mutex_t *mutex)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	table->number_of_philo = ft_atoi(av[1]);
	table->number_of_forks = table->number_of_philo;
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = (unsigned)ft_atoi(av[3]);
	table->time_to_sleep = (unsigned)ft_atoi(av[4]);
	table->start_simulation = get_current_millisecond();
	table->mutex = mutex;
	if (av[5])
		table->number_of_times_each_philo_must_eat = ft_atoi(av[5]);
	else
		table->number_of_times_each_philo_must_eat = -1;
}

void	philo_init(t_philo *philo, t_table *table, int id, int *death_flag)
{
	philo->id = id;
	philo->table = table;
	philo->someone_died = death_flag;
	philo->last_lunch_time = get_current_millisecond();
	philo->number_of_times_philo_must_eat =
									table->number_of_times_each_philo_must_eat;
}

void	mutex_forks_init(pthread_mutex_t *forks_mutex, int number_of_forks)
{
	int		i;

	i = 0;
	while (i < number_of_forks)
		pthread_mutex_init(&forks_mutex[i++], NULL);
}

void	mutex_forks_destroy(pthread_mutex_t *forks_mutex, int number_of_forks)
{
	int		i;

	i = 0;
	while (i < number_of_forks)
		pthread_mutex_destroy(&forks_mutex[i++]);
}
