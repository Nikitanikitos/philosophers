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
# define PHILO_ONE_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define FALSE	0
# define TRUE	1

typedef struct			s_table
{
	int					number_of_philo;
	int					number_of_forks;
	int					number_of_times_each_philo_must_eat;
	long int			time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	long int			start_simulation;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		*waiter;
}						t_table;

typedef struct			s_philo
{
	int					id;
	int					*is_die;
	int					number_of_times_philo_must_eat;
	long int			last_lunch_time;
	t_table				*table;

}						t_philo;

void					table_init(t_table *table, char **av,
														pthread_mutex_t *mutex);
void					philo_init(t_philo *philo, t_table *table, int id,
															int *death_flag);
void					mutex_forks_init(pthread_mutex_t *forks_mutex,
														int number_of_forks);
void					mutex_forks_destroy(pthread_mutex_t *forks_mutex,
														int number_of_forks);

void					*action(void *thread_data);
void					write_status_philo(t_philo *philo, char *action);

void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(long int nbr, int fd);
void					ft_putstr_fd(char *s, int fd);

int						right_fork(int philo_id, int number_of_philo);
long int				get_current_millisecond(void);
void					*check_death(void *thread_data);

int						ft_atoi(char *nptr);
int						ft_strlen(const char *str);
int						check_arguments(int ac, char **av);

char					*ft_itoa(long int n);
char					*ft_strjoin(char const *s1, char const *s2);

char					ft_isdigit(char c);

#endif
