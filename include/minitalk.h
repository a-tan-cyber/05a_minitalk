/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 22:00:37 by amtan             #+#    #+#             */
/*   Updated: 2026/01/02 19:30:14 by amtan            ###   ########.fr       */
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

/* src/client_send.c */
void			client_send_message(pid_t server_pid, const char *msg);

/* protocol_bits.c */
int				bit_from_signal(int sig);
int				signal_from_bit(int bit);
unsigned char	set_bit(unsigned char byte, int bit_index, int bit_value);

/* server_signal.c */
void			server_install_handlers(void);

/* utils.c */
int				parse_pid(const char *s);
void			fatal(char *msg);

#endif