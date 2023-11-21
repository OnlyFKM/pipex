/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:56:02 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/18 18:40:25 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_joinslash(char *cmd)
{
	int		len;
	char	*new;
	int		i;

	len = ft_strlen(cmd);
	new = malloc(len + 2);
	new[0] = '/';
	i = 0;
	while (i < (len + 2))
	{
		new[i + 1] = cmd[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_execution(char *argv, char **envp)
{
	char	**cmd;
	char	*abs_path;
	char	*new_char;

	cmd = ft_split(argv, ' ');
	new_char = ft_joinslash(cmd[0]);
	abs_path = ft_find_path(envp, new_char);
	free(new_char);
	execve(abs_path, cmd, envp);
}

void	ft_child_process(char *argv[], char **envp, int *fd)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		ft_error("Error opening input file\n");
	if (dup2(fd[1], STDOUT_FILENO) == -1 || dup2(fd_in, STDIN_FILENO) == -1)
		ft_error("Error in dup2\n");
	close(fd[0]);
	close(fd[1]);
	ft_execution(argv[2], envp);
}

void	ft_parent_process(char *argv[], char **envp, int *fd)
{
	int		fd_out;

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		ft_error("Error in dup2\n");
	close(fd[1]);
	close(fd[0]);
	ft_execution(argv[3], envp);
}

int	main(int argc, char *argv[], char **envp)
{
	pid_t	pid;
	int		fd_pipex[2];

	if (argc != 5)
	{
		ft_printf("Error\nExample: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd_pipex) < 0)
		ft_error("Error in pipe");
	pid = fork();
	if (pid == -1)
		ft_error("Error in fork\n");
	if (pid == 0)
		ft_child_process(argv, envp, fd_pipex);
	else
	{
		waitpid(pid, NULL, 0);
		ft_parent_process(argv, envp, fd_pipex);
	}
	return (0);
}
