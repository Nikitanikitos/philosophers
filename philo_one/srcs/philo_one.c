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

void	start_threads(t_table *table)
{
	pthread_t		threads[table->number_of_philo];
	pthread_mutex_t	forks_mutex[table->number_of_forks];
	t_philo			philo[table->number_of_philo];
	int				i;

	mutex_forks_init(forks_mutex, table->number_of_forks);
	table->forks_mutex = forks_mutex;
	while (table->number_of_times_each_philo_must_eat)
	{
		table->number_of_times_each_philo_must_eat--;
		i = 0;
		while (i < table->number_of_philo)
		{
			philo_init(&philo[i], table, i);
			pthread_create(&threads[i], NULL, action, &philo[i]);
			i++;
		}
		i = 0;
		while (i < table->number_of_philo)
			pthread_join(threads[i++], NULL);
	}
	mutex_forks_destroy(forks_mutex, table->number_of_forks);
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

