/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:39:05 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 21:32:48 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static size_t	count_digits(unsigned int num);
static void		num_to_str(unsigned int num, char *s, int is_neg, size_t len);

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	num;
	int				is_neg;
	size_t			digits;
	size_t			len;

	is_neg = (n < 0);
	num = (unsigned int)n;
	if (is_neg)
		num = -num;
	digits = count_digits(num);
	len = is_neg + digits;
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	num_to_str(num, s, is_neg, len);
	return (s);
}

static size_t	count_digits(unsigned int num)
{
	size_t	count;

	count = 1;
	while (num > 9)
	{
		count++;
		num = num / 10;
	}
	return (count);
}

static void	num_to_str(unsigned int num, char *s, int is_neg, size_t len)
{
	s[len] = '\0';
	if (num == 0)
		s[0] = '0';
	while (num > 0)
	{
		s[len - 1] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	if (is_neg)
		s[0] = '-';
}
