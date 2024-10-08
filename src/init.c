/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:24:29 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 12:42:44 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void	init_signal(int signo, void (*handler)(int), struct sigaction *sa)
{
	if (sigemptyset(&sa->sa_mask) == -1)
		perror("sigemptyset");
	sa->sa_flags = SA_RESTART;
	if (!handler)
		sa->sa_handler = SIG_IGN;
	else
		sa->sa_handler = handler;
	if (sigaction(signo, sa, NULL) == -1)
		perror("sigaction");
}

static void	disable_ctrlc_echo(void)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	disable_ctrlc_echo();
	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->line = NULL;
	shell->env = get_env(env);
	shell->envp = env;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->exit_status = (int *)ft_calloc(1, sizeof(int));
	*shell->exit_status = 0;
	init_signal(SIGINT, handle_sigint, &shell->sigint);
	init_signal(SIGQUIT, handle_sigquit, &shell->sigquit);
	return (shell);
}
