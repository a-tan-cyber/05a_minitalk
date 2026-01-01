/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:50:30 by amtan             #+#    #+#             */
/*   Updated: 2025/11/23 00:33:40 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recur_putdigits_fd(unsigned int num, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	int				is_neg;
	unsigned int	num;

	is_neg = (n < 0);
	num = (unsigned int)n;
	if (is_neg)
	{
		num = -num;
		ft_putchar_fd('-', fd);
	}
	recur_putdigits_fd(num, fd);
}

static void	recur_putdigits_fd(unsigned int num, int fd)
{
	if (num > 9)
		recur_putdigits_fd(num / 10, fd);
	ft_putchar_fd(num % 10 + '0', fd);
}
