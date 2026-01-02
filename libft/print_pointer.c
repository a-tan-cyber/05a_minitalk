/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:30:21 by amtan             #+#    #+#             */
/*   Updated: 2025/12/05 19:35:13 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hex_uintptr_recur(uintptr_t n, size_t *printed);

int	print_pointer(uintptr_t addr, size_t *printed)
{
	int	tmp;
	int	ret;

	if (addr == 0)
		return (print_str("(nil)", printed));
	tmp = print_str("0x", printed);
	if (tmp < 0)
		return (-1);
	ret = print_hex_uintptr_recur(addr, printed);
	if (ret < 0)
		return (-1);
	return (ret + tmp);
}

static int	print_hex_uintptr_recur(uintptr_t n, size_t *printed)
{
	int		ret;
	int		tmp;
	char	*symbols;

	ret = 0;
	symbols = "0123456789abcdef";
	if (n >= (uintptr_t)16)
	{
		ret = print_hex_uintptr_recur(n / 16, printed);
		if (ret < 0)
			return (-1);
	}
	tmp = print_char(symbols[n % 16], printed);
	if (tmp < 0)
		return (-1);
	return (ret + tmp);
}
