/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:10:13 by amtan             #+#    #+#             */
/*   Updated: 2025/12/05 19:13:02 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_digit_recur(unsigned long n, int base, char *symbols,
				size_t *printed);

int	print_unsigned_base(unsigned long n, char specifier, size_t *printed)
{
	int		base;
	char	*symbols;

	if (specifier == 'd' || specifier == 'i' || specifier == 'u')
	{
		base = 10;
		symbols = "0123456789";
	}
	else if (specifier == 'x' || specifier == 'X')
	{
		base = 16;
		if (specifier == 'X')
			symbols = "0123456789ABCDEF";
		else
			symbols = "0123456789abcdef";
	}
	else
		return (-1);
	return (print_digit_recur(n, base, symbols, printed));
}

static int	print_digit_recur(unsigned long n, int base, char *symbols,
		size_t *printed)
{
	int	ret;
	int	tmp;

	ret = 0;
	if (n >= (unsigned long)base)
	{
		ret = print_digit_recur(n / base, base, symbols, printed);
		if (ret < 0)
			return (-1);
	}
	tmp = print_char(symbols[n % base], printed);
	if (tmp < 0)
		return (-1);
	return (ret + tmp);
}
