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

#include "philo_two.h"

void	threads_join(pthread_t *threads, int number_of_philo)
{
	int		i;

	i = 0;
	while (i < number_of_philo)
		pthread_join(threads[i++], NULL);
}

void	threads_create(pthread_t *threads, t_philo *philo,
													t_table *table, int is_die)
{
	int		i;

	i = 0;
	while (i < table->number_of_philo)
	{
		philo_init(&philo[i], table, i, &is_die);
		pthread_create(&threads[i], NULL, action, &philo[i]);
		i++;
	}
}

void	start_threads(t_table *table)
{
	pthread_t		threads[table->number_of_philo];
	sem_t			*sem_forks;
	t_philo			philo[table->number_of_philo];
	static int		is_die;

	sem_forks = sem_open(NULL, O_CREAT, NULL, table->number_of_forks);
	table->sem_forks = sem_forks;
	threads_create(threads, philo, table, is_die);
	threads_join(threads, table->number_of_philo);
	sem_close(sem_forks);
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