/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/09/23 12:29:50 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

static char	*create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp_prompt;
	char	*value;

	value = NULL;
	prompt = (char *)ft_calloc(BUFFER_SIZE, 1);
	tmp_prompt = prompt;
	ft_strlcpy(tmp_prompt, "\033[1;31mRaRe\033[0m:\033[1;34m", 24);
	tmp_prompt += 23;
	value = get_env_value(shell->env, "PWD");
	if (value)
	{
		ft_strlcpy(tmp_prompt, value, ft_strlen(value) + 1);
		tmp_prompt += ft_strlen(value);
	}
	ft_strlcpy(tmp_prompt, "\033[0m$ ", 7);
	if (value)
		free(value);
	return (prompt);
}

void	main_loop(t_shell *shell, int tester, char **arg_input, int *i)
{	
	char	*prompt;
	
	prompt = create_prompt(shell);
	if (!tester)
	{
		shell->line = readline(prompt);
		free(prompt);
		if (!shell->line)
			return ;
		if (!*shell->line)
		{
			free(shell->line);
			return ;
		}
		add_history(shell->line);
	}
	else
		shell->line = ft_strdup(arg_input[*i]);
	if (!shell->line)
		return ;
	if (!*shell->line)
	{
		free(shell->line);
		return ;
	}
	shell->tokens = tokenizer(shell, shell->line, shell->env);
	//print_token(shell->tokens);
	free(shell->line);
	shell->cmd = create_cmds(shell, shell->tokens);
	free_token(shell->tokens);
	parse_cmds(shell);
	//print_cmd(shell);
	execute_cmd(shell);
	shell->cmd->is_builtin = false;
	free_cmds(shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	//while (1)
		main_loop(shell, 0, NULL, NULL);
	ft_exit(shell, *(shell->exit_status));
}
