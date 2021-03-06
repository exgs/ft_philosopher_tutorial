/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:01:14 by yunslee           #+#    #+#             */
/*   Updated: 2021/12/06 03:20:24 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_doing(t_status status, t_philo *philo)
{
	// NOTE 이 함수에서 printf는 이런 것들이 호출 됬음. 적절한 조건문을 활용하길 바람.
	/*
	printf("is eating\n");
	printf("is sleeping\n");
	printf("is thinking\n");
	printf("has taken a fork\n");
	printf("has taken a fork\n");
	printf("is died\n");
	*/
	if (status == EATING)
		printf("\x1b[34m%d is eating.\n\x1b[0m", philo->whoami);
	else if (status == SLEEPING)
		printf("\x1b[32m%d is sleeping.\n\x1b[0m", philo->whoami);
	else if (status == THINKING)
		printf("\x1b[33m%d is thinking.\n\x1b[0m", philo->whoami);
	else if (status == LEFT_TAKEN)
		printf("%d has taken a left fork.\n", philo->whoami);
	else if (status == RIGHT_TAKEN)
		printf("%d has taken a right fork.\n", philo->whoami);
	else if (status == DEAD)
	{
		printf("\x1b[31m%d died.\n\x1b[0m", philo->whoami);
		info()->anyone_dead = TRUE;
		return (END);
	}
	return (CONTINUE);
}

int		doing(t_status status, t_philo *philo, unsigned long interval)
{
	int				ret;
	unsigned long	times;

	// times = interval;
	if (info()->anyone_dead == TRUE)
		return (END);
	pthread_mutex_lock(&(info()->print_mutex));
	times = get_relative_time();
	if (info()->anyone_dead == FALSE)
	{
		if (status == EATING)
			philo->when_eat = times;
		printf("%lums ", times);
		ret = print_doing(status, philo);
	}
	else
		ret = END;
	pthread_mutex_unlock(&(info()->print_mutex));
	return (ret);
}

int	is_all_philos_full()
{
	int i;
	
	i = 0;
	if (info()->meal_full == 0)
		return (FALSE);
	while (info()->meal_full > 0 && i < info()->number_of_philosophers)
	{
		if (info()->full_list[i] == 0)
			break ;
		i++;
	}
	if (i == info()->number_of_philosophers)
	{
		// info()->anyone_dead = TRUE;
		// printf("\x1b[35mEnd of meal\n\x1b[0m");
		// doing(MEAL, philo, get_relative_time());
		return (TRUE);
	}
	return (FALSE);
}

// 하나의 철학자에 대한 모니터링
void	*monitoring(void *param)
{
	t_philo			*philo;
	unsigned long	time;

	philo = (t_philo *)param;
	
	while (1)
	{
		// NOTE 확인해야하는 것
		// 1. 어느 한명이라도 죽었다면, break; (내가 아니더라도, 누군가 죽었으면 Stop!)
		if (info()->anyone_dead == TRUE)
			return (0);
		// 2. 인자가 주어진 경우 모든 철학자가 밥을 먹었으면, break;

		// 3. 시간 계산을 해서, 현재 이 모니터함수가 관찰하고 있는 철학자가 죽었다면, dead 출력 후 break;
		if (philo->when_eat + info()->time_to_die < get_relative_time())
		{
			doing(DEAD, philo, get_relative_time());
			return (0);
		}
		accurate_sleep(3);
	}
}

//한 명의 철학자에 대한 정보가 넘어옴
void	*philo_do(void *param)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)param;
	pthread_create(&thread, NULL, monitoring, philo);

	if (philo->whoami % 2)
		accurate_sleep(3);
	// NOTE 먹고 자고 생각하고
	while (1)
	{
		// 1. 먹고
		if (eat(philo, info()) == END)
			break ;
		// 2. 자고
		if (doing(SLEEPING, philo, get_relative_time()) == END)
			break ;
		spend_time_of(SLEEPING);
		// 3. 생각하고
		if (doing(THINKING, philo, get_relative_time()) == END)
			break;
	}
	pthread_join(thread, NULL);
	return (0);
}
