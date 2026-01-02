/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:16:06 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 21:01:11 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	print_char(int c, size_t *printed);
int	print_str(char *str, size_t *printed);
int	print_unsigned_base(unsigned long n, char specifier, size_t *printed);
int	print_signed_base(long n, char specifier, size_t *printed);
int	print_pointer(uintptr_t addr, size_t *printed);

#endif