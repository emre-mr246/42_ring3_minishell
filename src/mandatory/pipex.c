
#include "../inc/pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../inc/pipex.h"
#include "../lib/libft/libft.h"
#include <unistd.h>

void	input_error(void)
{
	printf("%s", "\033[1;31m=== ERROR ======\n");
	printf("%s", "$ ./pipex infile cmd1 cmd2 outfile\n");
	printf("%s", "OR\n");
	printf("%s", "$ ./pipex_bonus infile cmd1 cmd2 ... cmdn outfile\n");
	printf("%s", "$ ./pipex_bonus here_doc LIMITER cmd1 cmd2 file\n");
	exit(EXIT_FAILURE);
}

void	error(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		result;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error("command splitting failed");
	path = find_valid_path(cmd[0], envp);
	if (!path)
	{
		free_array(cmd);
		error("command not found in PATH");
	}
	result = execve(path, cmd, envp);
	free(path);
	free_array(cmd);
	if (result == -1)
		error("execve failed");
}

char	*find_valid_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*valid_path;
	char	*tmp;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0 && envp[i])
		i++;
	tmp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	paths = ft_split(tmp, ':');
	if (!paths || !*paths)
		error("An error occurred while creating the paths.");
	free(tmp);
	i = 0;
	while (paths[i])
	{
		valid_path = make_path(paths[i++], cmd);
		if (valid_path != NULL)
			break ;
	}
	free_array(paths);
	return (valid_path);
}

char	*make_path(char *uncompleted_path, char *cmd)
{
	char	*path_part;
	char	*valid_path;

	path_part = ft_strjoin(uncompleted_path, "/");
	if (!path_part)
		error("An error occurred while creating the path_part.");
	valid_path = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(valid_path, F_OK) < 0)
		return (NULL);
	return (valid_path);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}


void	child_process(char **argv, char **envp, int *fd)
{
	int	input_file;

	input_file = open(argv[1], O_RDONLY, 0444);
	if (input_file == -1)
		error("Unable to open input_file");
	dup2(input_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	out_file;

	out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_file == -1)
		error("Unable to open outFile");
	dup2(fd[0], STDIN_FILENO);
	dup2(out_file, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

int	ft_pipe(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		input_error();
	if (pipe(fd) == -1)
		error("Pipe creation failed");
	pid = fork();
	if (pid == -1)
		error("Fork failed");
	if (pid == 0)
		child_process(argv, envp, fd);
	waitpid(-1, NULL, 0);
	if (pid != 0)
		parent_process(argv, envp, fd);
	return (0);
}