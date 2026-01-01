/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 22:00:37 by amtan             #+#    #+#             */
/*   Updated: 2026/01/01 19:35:21 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>

typedef struct s_server_state
{
	unsigned char	current_byte;
	int				bit_index;
	pid_t			client_pid;
}	t_server_state;

void			client_send_message(pid_t server_pid, const char *msg);
void			client_send_char(pid_t server_pid, unsigned char c);

int				bit_from_signal(int sig);
int				signal_from_bit(int bit);
unsigned char	set_bit(unsigned char byte, int bit_index, int bit_value);

void			server_install_handlers(void);

int				parse_pid(const char *s);
void			fatal(const char *msg);

#endif