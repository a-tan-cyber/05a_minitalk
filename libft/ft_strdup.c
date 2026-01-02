/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:09:04 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 21:34:58 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	total;

	total = ft_strlen(s) + 1;
	dup = malloc(total);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, total);
	return (dup);
}
