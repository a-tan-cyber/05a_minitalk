/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:05:04 by amtan             #+#    #+#             */
/*   Updated: 2025/12/05 17:04:36 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_signed_base(long n, char specifier, size_t *printed)
{
	unsigned long	un;
	int				ret;
	int				tmp;

	tmp = 0;
	if (n < 0)
	{
		tmp = print_char('-', printed);
		if (tmp < 0)
			return (-1);
		un = (unsigned long)(-(n + 1)) + 1;
	}
	else
		un = (unsigned long)n;
	ret = print_unsigned_base(un, specifier, printed);
	if (ret < 0)
		return (-1);
	return (ret + tmp);
}
