/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:02:40 by amtan             #+#    #+#             */
/*   Updated: 2025/11/20 19:27:05 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*p;
	const unsigned char	*last;
	unsigned char		ch;

	p = (const unsigned char *)s;
	last = NULL;
	ch = (unsigned char)c;
	while (*p)
	{
		if (*p == ch)
			last = p;
		p++;
	}
	if (ch == '\0')
		return ((char *)p);
	return ((char *)last);
}
