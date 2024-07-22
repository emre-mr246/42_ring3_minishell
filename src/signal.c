/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:08:48 by emgul             #+#    #+#             */
/*   Updated: 2024/07/22 23:02:23 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../lib/libft/libft.h"

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
