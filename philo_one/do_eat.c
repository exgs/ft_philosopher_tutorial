/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:00:55 by yunslee           #+#    #+#             */
/*   Updated: 2021/12/19 16:57:57 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo, t_info *info)
{
	// 1. 누군가 죽었는지 판단해서 죽었다면, 바로 return 
	if (info->anyone_dead)
		return (END);
	// 2. 먹는 알고리즘 info->forks에 대해서 mutex가 쓰임. 매우매우 중요한 부분
	pthread_mutex_lock(&(info->forks[philo->left_fork_num]));
	if (doing(LEFT_TAKEN, philo, get_relative_time()) == END)
	{
		pthread_mutex_unlock(&(info->forks[philo->left_fork_num]));
		return (END);
	}
	pthread_mutex_lock(&(info->forks[philo->right_fork_num]));
	if (doing(RIGHT_TAKEN, philo, get_relative_time()) == END)
	{
		pthread_mutex_unlock(&(info->forks[philo->left_fork_num]));
		pthread_mutex_unlock(&(info->forks[philo->right_fork_num]));
		return (END);
	}
	if (doing(EATING, philo, get_relative_time()) == END)
	{
		pthread_mutex_unlock(&(info->forks[philo->left_fork_num]));
		pthread_mutex_unlock(&(info->forks[philo->right_fork_num]));
		return (END);
	}
	// philo->when_eat = get_relative_time();
	spend_time_of(EATING);
	philo->meal_num++;
	if (info->meal_full > 0 && philo->meal_num == info->meal_full)
		info->full_list[philo->whoami - 1] = 1;
	pthread_mutex_unlock(&(info->forks[philo->left_fork_num]));
	pthread_mutex_unlock(&(info->forks[philo->right_fork_num]));
	return (CONTINUE);
}
