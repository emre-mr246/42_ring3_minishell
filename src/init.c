/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:24:29 by emgul             #+#    #+#             */
/*   Updated: 2024/07/24 23:21:45 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <bits/sigaction.h>

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->line = (NULL);
	shell->std_input = dup(0);
	shell->env = get_env(env);
	shell->envp = env;
	shell->tokens = NULL;
	shell->cmd 	= NULL;
	shell->sigint.sa_handler = handle_sigint;
	shell->sigint.sa_flags = SA_RESTART;
	// shell->sigint.sa_mask = 
	return (shell);
}