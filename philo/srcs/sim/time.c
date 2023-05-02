/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:25:26 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/02 15:13:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

long	set_time(t_philo *philo, int mode)
{
	philo->cur = get_time() - philo->data->start;
	philo->tod = ft_lmax((philo->cur + philo->tod) * mode, philo->tod);
	return (philo->cur);
}
