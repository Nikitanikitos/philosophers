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

#include <signal.h>
#include "philo_three.h"

void	kill_all_childs(t_table *table, int *pids)
{
	int 	i;

	sem_wait(table->sem);
	i = 0;
	while (i < table->number_of_philo)
		kill(pids[i++], SIGKILL);
	sem_post(table->sem);
}

void	fork_create(t_table *table)
{
	int			i;
	t_philo		philo[table->number_of_philo];
	int 		pids[table->number_of_philo];
	pid_t		pid;

	i = 0;
	sem_wait(table->sem);
	while (i < table->number_of_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_init(&philo[i], table, i);
			action(&philo[i]);
			exit(0);
		}
		else
			pids[i++] = pid;
	}
	kill_all_childs(table, pids);
	wait(0);
}

void	start_forks(t_table *table)
{
	sem_t			*sem_forks;

	sem_unlink("/forks");
	sem_forks = sem_open("/forks", O_CREAT, NULL, table->number_of_forks);
	table->sem_forks = sem_forks;
	fork_create(table);
	sem_close(sem_forks);
}

int		main(int ac, char **av)
{
	t_table		table;
	sem_t		*sem;

	if (check_arguments(ac, av))
		return (1);
	sem_unlink("/check_die");
	sem = sem_open("/check_die", O_CREAT, NULL, 1);
	table_init(&table, av, sem);
	start_forks(&table);
	sem_close(sem);
	return (0);
}
