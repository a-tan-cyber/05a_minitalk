/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:36:12 by amtan             #+#    #+#             */
/*   Updated: 2026/01/03 11:23:57 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <signal.h>
#include <unistd.h>

#include "libft.h"

#define MT_ACK_BIT 1
#define MT_ACK_MSG 2

static volatile sig_atomic_t	g_client_ack;

static void	client_ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_client_ack |= MT_ACK_BIT;
	else if (sig == SIGUSR2)
		g_client_ack |= MT_ACK_MSG;
}

static void	client_install_ack_handlers(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = client_ack_handler;
	if (sigemptyset(&sa.sa_mask) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR1) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR2) == -1
		|| sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		fatal("minitalk: failed to install client ACK handlers");
}

static void	client_send_bit(pid_t server_pid, int bit)
{
	int	sig;

	g_client_ack &= ~MT_ACK_BIT;
	sig = signal_from_bit(bit);
	if (kill(server_pid, sig) == -1)
		fatal("minitalk: failed to send signal");
	while ((g_client_ack & MT_ACK_BIT) == 0)
		pause();
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
	client_install_ack_handlers();
	g_client_ack = 0;
	while (*msg != '\0')
	{
		client_send_char(server_pid, (unsigned char)*msg);
		msg++;
	}
	client_send_char(server_pid, '\0');
	while ((g_client_ack & MT_ACK_MSG) == 0)
		pause();
}
