/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 20:24:21 by imicah            #+#    #+#             */
/*   Updated: 2020/09/30 20:24:22 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define FALSE	0
# define TRUE	1

typedef struct			 s_table
{
	int					number_of_philosophers;
	int 				number_of_forks;
	int					time_to_die;
	int 				time_to_eat;
	int 				time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int 				philosopher_id;
	struct timeval		timeval_start_simulation;
	pthread_mutex_t		*mutex;
}						t_table;

void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(unsigned long nbr, int fd);
void					ft_putstr_fd(char *s, int fd);

int						ft_atoi(char *nptr);
int						ft_strlen(const char *str);
int						check_arguments(int ac, char **av);

char					ft_isdigit(char c);

#endif
