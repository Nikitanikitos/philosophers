/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 20:24:15 by imicah            #+#    #+#             */
/*   Updated: 2020/09/30 20:24:17 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	table_init(t_table *table, char **av, pthread_mutex_t *mutex)
{
	struct	timeval	timeval;

	gettimeofday(&timeval, NULL);
	table->number_of_philosophers = ft_atoi(av[1]);
	table->number_of_forks = table->number_of_philosophers;
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	table->philosopher_id = 0;
	table->timeval_start_simulation = timeval;
	table->mutex = mutex;
	if (av[5])
		table->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		table->number_of_times_each_philosopher_must_eat = -1;
}

void	write_status_philosopher(t_table *table, char *action)
{
	struct timeval	timeval;
	unsigned long	current_millisecond;

	gettimeofday(&timeval, NULL);
	current_millisecond = (table->timeval_start_simulation.tv_usec -
						   timeval.tv_usec) / 1000;
	ft_putnbr_fd(current_millisecond, 1);
	ft_putstr_fd(" ms: ", 1);
	ft_putnbr_fd(table->philosopher_id, 1);
	ft_putendl_fd(action, 1);
}

void	eating(t_table *table)
{
	struct timeval	timeval;
	unsigned long	current_millisecond;

	while (table->number_of_forks < 2)
		continue;
	pthread_mutex_lock(table->mutex);
	write_status_philosopher(table, " philosopher is eating");
	table->number_of_forks -= 2;
	usleep(table->time_to_eat);
	table->number_of_forks += 2;
	pthread_mutex_unlock(table->mutex);
}


void	sleeping(t_table *table)
{
	pthread_mutex_lock(table->mutex);
	write_status_philosopher(table, " philosopher is sleeping");
	pthread_mutex_unlock(table->mutex);
	usleep(table->time_to_sleep);
}

void	*action(void *thread_data)
{
	t_table		*table;

	table = (t_table*)thread_data;
	eating(table);
	sleeping(table);
	return (NULL);
}

void	start_threads(t_table *table)
{
	pthread_t	threads[table->number_of_philosophers];
	int			i;

	while (table->number_of_times_each_philosopher_must_eat)
	{
		table->number_of_times_each_philosopher_must_eat--;
		i = 0;
		while (i < table->number_of_philosophers)
		{
			table->philosopher_id++;
			pthread_create(&threads[i++], NULL, action, table);
		}
		i = 0;
		while (i < table->number_of_philosophers)
			pthread_join(threads[i++], NULL);
	}
}

int		main(int ac, char **av)
{
	t_table					table;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (check_arguments(ac, av))
		return (1);
	table_init(&table, av, &mutex);
	start_threads(&table);
	pthread_mutex_destroy(&mutex);
	return (0);
}
