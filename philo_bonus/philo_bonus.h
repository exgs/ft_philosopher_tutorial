/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:10:20 by yunslee           #+#    #+#             */
/*   Updated: 2021/12/19 17:04:24 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>

# define FALSE 0
# define TRUE 1
# define END 0
# define CONTINUE 1

typedef enum
{
	EATING = 0,
	SLEEPING,
	THINKING,
	LEFT_TAKEN,
	RIGHT_TAKEN,
	DEAD
}	t_status;

struct s_info;

typedef struct	s_philo
{
	pid_t			pid;
	int				whoami; //몇 번째 철학자인가
	unsigned long	when_eat;
	int				meal_num;
	struct s_info	*info;
}				t_philo;

typedef struct	s_info
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_full;
	unsigned long	basetime;
	int				anyone_dead;
	sem_t			*forks; // #(philos)
	sem_t			*print_sem; // #1
	sem_t			*eat_people; // #(philos) / 2
	int				*full_list; //다 먹은 철학자 판별해주는 역할(?)
	t_philo			*philos;
}				t_info;


int				g_philo_num;

/*
** main.c
*/
int				start(t_philo *philos, t_info *info);
int				main(int argc, char *argv[]);
void			*test(void *param);
void			free_all(t_philo *philos);

/*
** setting.c
*/
t_info			*info(void);
int				set_info_argv(t_info *info, int argc, char *argv[]);
void			mutex_fork_init(t_info *info); //존재하지 않음.
int				mutex_init(t_info *info);
void			print_info(t_info *info);
int				set_info(t_info *info);
int				set_philos(t_philo *philos);

/*
** ft_atoi.c
*/
int				ft_atoi(const char *str);

/*
** time.c
*/
unsigned long	get_relative_time();
unsigned long	get_absolute_time();
int				spend_time_of(t_status doing);
void			accurate_sleep(unsigned long milisecond);

/*
** do.c
*/
int				eat(t_philo *philo, t_info *info);
void			*monitoring(void *param);
int				doing(t_status status, t_philo *philo, unsigned long interval);
void			*philo_do(void *param);
int				print_doing(t_status status, t_philo *philo);
int				is_all_philos_full();
// int				is_all_philos_full(t_philo *philo);


/*
** do_eat.c
*/
int				eat(t_philo *philo, t_info *info);
#endif
