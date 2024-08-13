/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/08/14 00:57:59 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void ft_exit(int exit_code)
{
	rl_clear_history();
	exit(exit_code);
}

static char *create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strjoin("\033[1;31mRaRe\033[0m$:\033[1;34m", get_env_value(shell->env, "PWD"));
	tmp = prompt;
	prompt = ft_strjoin(tmp, "\033[0m$ ");
	free(tmp);
	return (prompt);
}
void	main_loop(t_shell *shell, int tester, char **arg_input, int *i)
{
	if (!tester)
	{
		shell->line = readline(create_prompt(shell));
		if (!shell->line)
		{
			free(shell->line); // bakılacak
			return ;
		}
		add_history(shell->line);
	}
	else
		shell->line = arg_input[*i];
	shell->tokens = tokenizer(shell->line, shell->env);
	if (!shell->tokens)
		return ;
	shell->cmd = create_cmd(*(shell->tokens));
	remove_redirs(shell);
	dollar_sign(shell);
	print_cmd(shell);
	handle_builtins_main(shell);
	execute_cmd(shell);
	shell->cmd->is_builtin = false;
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	while (1)
		main_loop(shell, 0, NULL, NULL);
	ft_exit(0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell		*shell;
// 	char	**arg_input;
// 	int		i;

// 	shell = init_shell(envp);
// 	if (!shell)
// 		return (-1);
// 	if (argc == 3 && ft_strncmp(argv[1], "-c", higher_len(argv[1], "-c")) == 0 && argv[2])
// 	{
// 		arg_input = ft_split(argv[2], ';');
// 		if (!arg_input)
// 			exit(1);
// 		i = 0;
// 		while (arg_input[i])
// 		{
// 			main_loop(shell, 1, arg_input, &i);
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		//while (1)
// 			main_loop(shell, 0, NULL, NULL);
// 	}
// 	// Free data and exit minishell when done

// }