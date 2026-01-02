/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:52:09 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 19:22:12 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minitalk.h"

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
		fatal("Usage: ./client <server_pid> <string>");
	server_pid = (pid_t)parse_pid(argv[1]);
	if (server_pid <= 0)
		fatal("minitalk: invalid server pid");
	if (kill(server_pid, 0) == -1)
		fatal("minitalk: server pid not reachable");
	client_send_message(server_pid, argv[2]);
	return (0);
}
