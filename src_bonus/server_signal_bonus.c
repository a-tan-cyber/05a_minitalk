/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_signal_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:37:24 by amtan             #+#    #+#             */
/*   Updated: 2026/01/03 11:23:46 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <signal.h>
#include <unistd.h>

#include "libft.h"

static t_server_state	g_svr;

static void	server_reset_byte(void)
{
	g_svr.current_byte = 0;
	g_svr.bit_index = 0;
}

static void	server_reset_state(void)
{
	server_reset_byte();
	g_svr.client_pid = 0;
}

static void	server_signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	pid_t			sender_pid;
	int				bit;
	unsigned char	c;

	(void)ucontext;
	sender_pid = info->si_pid;
	if (g_svr.client_pid != 0 && g_svr.client_pid != sender_pid)
		server_reset_state();
	g_svr.client_pid = sender_pid;
	bit = bit_from_signal(sig);
	g_svr.current_byte = set_bit(g_svr.current_byte, 7 - g_svr.bit_index, bit);
	g_svr.bit_index++;
	if (g_svr.bit_index == 8)
	{
		c = g_svr.current_byte;
		if (c != '\0')
			write(1, &c, 1);
		server_reset_byte();
		if (c == '\0')
		{
			g_svr.client_pid = 0;
			kill(sender_pid, SIGUSR2);
		}
	}
	kill(sender_pid, SIGUSR1);
}

void	server_install_handlers(void)
{
	struct sigaction	sa;

	server_reset_state();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_signal_handler;
	if (sigemptyset(&sa.sa_mask) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR1) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR2) == -1
		|| sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		fatal("minitalk: failed to install signal handlers");
}
