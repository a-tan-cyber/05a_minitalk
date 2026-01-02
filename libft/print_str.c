/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:47:00 by amtan             #+#    #+#             */
/*   Updated: 2025/12/05 17:00:31 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(char *str, size_t *printed)
{
	int	tmp;
	int	ret;

	if (!str)
		str = "(null)";
	ret = 0;
	while (*str != '\0')
	{
		tmp = print_char((int)*str, printed);
		if (tmp < 0)
			return (-1);
		str++;
		ret += tmp;
	}
	return (ret);
}
