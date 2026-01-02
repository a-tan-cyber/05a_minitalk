/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:17 by amtan             #+#    #+#             */
/*   Updated: 2025/11/22 11:36:05 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*p;
	unsigned char		ch;

	p = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (*p)
	{
		if (*p == ch)
			return ((char *)p);
		p++;
	}
	if (ch == '\0')
		return ((char *)p);
	return (NULL);
}
