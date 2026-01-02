/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:48:24 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 16:30:40 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minitalk.h"

int	bit_from_signal(int sig)
{
	if (sig == SIGUSR1)
		return (0);
	if (sig == SIGUSR2)
		return (1);
	return (-1);
}

int	signal_from_bit(int bit)
{
	if (bit == 0)
		return (SIGUSR1);
	if (bit == 1)
		return (SIGUSR2);
	return (-1);
}

unsigned char	set_bit(unsigned char byte, int bit_index, int bit_value)
{
	unsigned char	mask;

	if (bit_index < 0 || bit_index > 7)
		return (byte);
	mask = (unsigned char)(1u << bit_index);
	if (bit_value != 0)
		byte = (unsigned char)(byte | mask);
	else
		byte = (unsigned char)(byte & (unsigned char) ~mask);
	return (byte);
}
