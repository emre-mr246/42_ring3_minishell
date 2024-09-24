/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:08:48 by emgul             #+#    #+#             */
/*   Updated: 2024/09/24 12:45:50 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include "readline/readline.h"

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

void	handle_sigquit(int signo)
{
	printf("sigint\n");
	if (signo == SIGQUIT)
		exit(131);
}

void	child_signal_handler(int signum)
{
	printf("child signal handler\n");
	if (signum == SIGINT)
		exit(130);
	else if (signum == SIGQUIT)
		exit(131);
}
