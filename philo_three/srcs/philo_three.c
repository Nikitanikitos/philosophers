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

#include "philo_three.h"

void	kill_all_childs(t_table *table, int *pids)
{
	int		i;

	sem_wait(table->kill_childs);
	i = 0;
	while (i < table->number_of_philo)
		kill(pids[i++], SIGKILL);
	sem_post(table->kill_childs);
}

void	fork_create(t_table *table, sem_t *sem_output_death)
{
	int			i;
	pid_t		pid;
	int			pids[table->number_of_philo];
	t_philo		philo[table->number_of_philo];

	i = 0;
	sem_wait(table->kill_childs);
	while (i < table->number_of_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_init(&philo[i], table, i, sem_output_death);
			action(&philo[i]);
			exit(0);
		}
		else
			pids[i++] = pid;
	}
	kill_all_childs(table, pids);
}

void	start_forks(t_table *table)
{
	sem_t	*sem_forks;
	sem_t	*sem_output_death;

	sem_unlink("/kill_childs");
	sem_unlink("/forks");
	sem_output_death = sem_open("/output_death", O_CREAT, NULL, 1);
	sem_forks = sem_open("/forks", O_CREAT, NULL, table->number_of_forks);
	table->sem_forks = sem_forks;
	fork_create(table, sem_output_death);
	sem_post(sem_output_death);
	sem_close(sem_output_death);
	sem_close(sem_forks);
}

int		main(int ac, char **av)
{
	t_table		table;
	sem_t		*sem_kill_child;

	if (check_arguments(ac, av))
		return (1);
	sem_unlink("/output_death");
	sem_kill_child = sem_open("/kill_childs", O_CREAT, NULL, 1);
	table_init(&table, av, sem_kill_child);
	start_forks(&table);
	sem_close(sem_kill_child);
	return (0);
}
