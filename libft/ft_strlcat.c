/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:09:30 by amtan             #+#    #+#             */
/*   Updated: 2025/11/20 19:26:50 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	while (dst_len < size && dst[dst_len] != '\0')
		dst_len++;
	i = dst_len;
	src_len = 0;
	while (src[src_len] != '\0')
	{
		if (i + 1 < size)
		{
			dst[i] = src[src_len];
			i++;
		}
		src_len++;
	}
	if (dst_len < size)
		dst[i] = '\0';
	return (dst_len + src_len);
}
