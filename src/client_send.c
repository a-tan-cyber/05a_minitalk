/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:54:01 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 21:49:40 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <signal.h>
#include <unistd.h>

#define CLIENT_SEND_DELAY_US 200

static void	client_send_bit(pid_t server_pid, int bit)
{
	int	sig;

	sig = signal_from_bit(bit);
	if (sig == -1)
		fatal("minitalk: invalid bit");
	if (kill(server_pid, sig) == -1)
		fatal("minitalk: failed to send signal");
	usleep(CLIENT_SEND_DELAY_US);
}

static void	client_send_char(pid_t server_pid, unsigned char c)
{
	int	shift;
	int	bit;

	shift = 7;
	while (shift >= 0)
	{
		bit = (c >> shift) & 1;
		client_send_bit(server_pid, bit);
		shift--;
	}
}

void	client_send_message(pid_t server_pid, const char *msg)
{
	while (*msg != '\0')
	{
		client_send_char(server_pid, (unsigned char)*msg);
		msg++;
	}
	client_send_char(server_pid, '\0');
}
