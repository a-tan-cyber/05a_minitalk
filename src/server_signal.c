/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:53:37 by amtan             #+#    #+#             */
/*   Updated: 2026/01/01 22:57:54 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"
#include "libft.h"

static t_server_state	g_server;

static void	server_reset(void)
{
	g_server.current_byte = 0;
	g_server.bit_index = 0;
	g_server.client_pid = 0;
}

static void	die_install(void)
{
	write(2, "minitalk: sigaction setup failed\n",
		sizeof("minitalk: sigaction setup failed\n") - 1);
	exit(1);
}

static void	server_on_signal(int sig, siginfo_t *info, void *ucontext)
{
	pid_t			sender_pid;
	int				bit;
	unsigned char	c;

	(void)ucontext;
	sender_pid = info->si_pid;
	if (g_server.client_pid != 0 && g_server.client_pid != sender_pid)
	{
		g_server.current_byte = 0;
		g_server.bit_index = 0;
	}
	g_server.client_pid = sender_pid;
	bit = (sig == SIGUSR2);
	g_server.current_byte = set_bit(g_server.current_byte,
			7 - g_server.bit_index, bit);
	g_server.bit_index++;
	if (g_server.bit_index != 8)
		return ;
	c = g_server.current_byte;
	if (c != '\0')
		write(1, &c, 1);
	g_server.current_byte = 0;
	g_server.bit_index = 0;
	if (c == '\0')
		g_server.client_pid = 0;
}

void	server_install_handlers(void)
{
	struct sigaction	sa;

	server_reset();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_on_signal;
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
