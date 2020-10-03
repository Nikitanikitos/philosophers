/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:39:44 by imicah            #+#    #+#             */
/*   Updated: 2020/10/02 12:39:45 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long int	get_current_millisecond(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

char		*get_output_string(char *current_millisecond, char *id,
																char *action)
{
	int		total_size;
	int 	i;
	int 	q;
	char	*result;

	i = 0;
	total_size = ft_strlen(current_millisecond) + ft_strlen(id) +
															ft_strlen(action);
	result = (char*)malloc(sizeof(char ) * total_size + 2);
	q = 0;
	while (current_millisecond[q])
		result[i++] = current_millisecond[q++];
	q = 0;
	result[i++] = ' ';
	while (id[q])
		result[i++] = id[q++];
	q = 0;
	while (action[q])
		result[i++] = action[q++];
	result[i] = 0;
	free(current_millisecond);
	free(id);
	return (result);
}

void		write_status_philo(t_philo *philo, char *action)
{
	char	*output_string;

	if (*philo->is_die)
		return ;
	output_string = get_output_string(
			ft_itoa(get_current_millisecond() - philo->table->start_simulation),
			ft_itoa(philo->id + 1), action);
	ft_putstr_fd(output_string , 1);
}

int 		left_fork(int philo_id, int number_of_philo)
{
	return ((philo_id - 1 + number_of_philo) % number_of_philo);
}

int			right_fork(int philo_id, int number_of_philo)
{
	return ((philo_id + 1) % number_of_philo);
}

void		*check_death(void *thread_data)
{
	t_philo		*philo;

	philo = (t_philo*)thread_data;
	while (get_current_millisecond() - philo->last_lunch_time
												<= philo->table->time_to_die)
		;
	write_status_philo(philo, " is died...\n");
	*philo->is_die = 1;
	return (NULL);
}
