/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:50:37 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 14:48:08 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minitalk.h"
#include "libft.h"

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("%d\n", (int)pid);
	server_install_handlers();
	while (1)
		pause();
	return (0);
}

