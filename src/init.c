/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:24:29 by emgul             #+#    #+#             */
/*   Updated: 2024/07/19 18:07:33 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <stdlib.h>

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->line = NULL;
	shell->std_input = dup(0);
	shell->env = get_env(env);
	shell->envp = env;
	shell->tokens = NULL;
	shell->cmd 	= NULL;
	return (shell);
}