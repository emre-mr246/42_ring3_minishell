/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:24:29 by emgul             #+#    #+#             */
/*   Updated: 2024/08/13 23:09:02 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <bits/sigaction.h>
#include <stdio.h>
#include "../../lib/libft/libft.h"

void init_signal(int signo, void (*handler)(int), struct sigaction *sa)
{
	sa = (struct sigaction *)ft_calloc(1, sizeof(struct sigaction));
	if (sigemptyset(&sa->sa_mask) == -1)
		perror("sigemptyset");
    sa->sa_flags = SA_RESTART;
	if (!handler)
		sa->sa_handler = SIG_IGN;
	else
    	sa->sa_handler = handler;
    if (sigaction(signo, sa, NULL) == -1)
		perror("sigaction");
	return (sa);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->line = (NULL);
	shell->std_input = dup(0);
	shell->env = get_env(env);
	shell->envp = env;
	shell->tokens = NULL;
	shell->cmd 	= NULL;
	shell->last_exit_status = (int *)ft_calloc(1, sizeof(int));
	*shell->last_exit_status = 0;
	init_signal(SIGINT, handle_sigint, &shell->sigint);
	init_signal(SIGQUIT, handle_sigquit, &shell->sigquit);
	return (shell);
}