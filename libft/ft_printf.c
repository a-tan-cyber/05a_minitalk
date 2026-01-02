/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:41:17 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 21:34:17 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <limits.h>
#include <stdarg.h>

static int	print_next(const char **format, va_list *ap, size_t *printed);
static int	process_specifier(const char **format, va_list *ap,
				size_t *printed);
static int	print_unknown_specifier(char specifier, size_t *printed);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	printed;
	int		ret;

	if (!format)
		return (-1);
	va_start(ap, format);
	printed = 0;
	while (*format)
	{
		ret = print_next(&format, &ap, &printed);
		if (ret < 0)
		{
			va_end(ap);
			return (-1);
		}
		format++;
	}
	va_end(ap);
	if (printed > (size_t)INT_MAX)
		return (-1);
	return (printed);
}

static int	print_next(const char **format, va_list *ap, size_t *printed)
{
	int	ret;

	if (**format == '%')
	{
		if (!*(*format + 1))
			return (-1);
		(*format)++;
		if (**format == '%')
			ret = print_char('%', printed);
		else
			ret = process_specifier(format, ap, printed);
	}
	else
		ret = print_char((int)**format, printed);
	return (ret);
}

static int	process_specifier(const char **format, va_list *ap, size_t *printed)
{
	char	specifier;
	int		ret;

	specifier = **format;
	if (specifier == 'c')
		ret = print_char(va_arg(*ap, int), printed);
	else if (specifier == 's')
		ret = print_str(va_arg(*ap, char *), printed);
	else if (specifier == 'x' || specifier == 'X' || specifier == 'u')
		ret = print_unsigned_base((unsigned long)va_arg(*ap, unsigned int),
				specifier, printed);
	else if (specifier == 'd' || specifier == 'i')
		ret = print_signed_base((long)va_arg(*ap, int), specifier, printed);
	else if (specifier == 'p')
		ret = print_pointer((uintptr_t)va_arg(*ap, void *), printed);
	else
		ret = print_unknown_specifier(specifier, printed);
	return (ret);
}

static int	print_unknown_specifier(char specifier, size_t *printed)
{
	int	tmp1;
	int	tmp2;

	tmp1 = print_char('%', printed);
	if (tmp1 < 0)
		return (-1);
	tmp2 = print_char(specifier, printed);
	if (tmp2 < 0)
		return (-1);
	return (tmp1 + tmp2);
}
