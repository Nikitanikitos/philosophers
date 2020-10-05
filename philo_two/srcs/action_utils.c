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

#include "philo_two.h"

void	*check_death(void *thread_data)
{
	t_philo				*philo;

	philo = (t_philo*)thread_data;
	while (get_current_millisecond() - philo->last_lunch_time
												<= philo->table->time_to_die)
		usleep(10);
	sem_wait(philo->table->sem);
	write_status_philo(philo, " is died...\n");
	*philo->is_die = 1;
	sem_post(philo->table->sem);
	return (NULL);
}
