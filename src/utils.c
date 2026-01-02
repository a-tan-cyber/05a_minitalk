/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:49:30 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 19:54:13 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "minitalk.h"
#include "libft.h"

int	parse_pid(const char *s)
{
	long	n;
	int		i;

	if (s == NULL || s[0] == '\0')
		return (-1);
	n = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		n = (n * 10) + (s[i] - '0');
		if (n > INT_MAX)
			return (-1);
		i++;
	}
	if (n <= 0)
		return (-1);
	return ((int)n);
}

void	fatal(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}
