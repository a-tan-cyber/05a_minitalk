/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:53:37 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 17:14:42 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"
#include "libft.h"

static t_server_state	g_server;

static void	server_reset_byte(void)
{
	g_server.current_byte = 0;
	g_server.bit_index = 0;
}

static void	server_reset_state(void)
{
	server_reset_byte();
	g_server.client_pid = 0;
}

static void	die_install(void)
{
	write(2, "minitalk: failed to install signal handlers\n",
		sizeof("minitalk: failed to install signal handlers\n") - 1);
	exit(1);
}

static void	server_signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	pid_t			sender_pid;
	int				bit;
	unsigned char	c;

	(void)ucontext;
	sender_pid = info->si_pid;
	if (g_server.client_pid != 0 && g_server.client_pid != sender_pid)
		server_reset_byte();
	g_server.client_pid = sender_pid;
	bit = bit_from_signal(sig);
	if (bit == -1)
		return ;
	g_server.current_byte = set_bit(g_server.current_byte,
			7 - g_server.bit_index, bit);
	g_server.bit_index++;
	if (g_server.bit_index != 8)
		return ;
	c = g_server.current_byte;
	if (c != '\0')
		write(1, &c, 1);
	server_reset_byte();
	if (c == '\0')
		g_server.client_pid = 0;
}

void	server_install_handlers(void)
{
	struct sigaction	sa;

	server_reset_state();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_signal_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		die_install();
	if (sigaddset(&sa.sa_mask, SIGUSR1) == -1)
		die_install();
	if (sigaddset(&sa.sa_mask, SIGUSR2) == -1)
		die_install();
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		die_install();
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		die_install();
}
