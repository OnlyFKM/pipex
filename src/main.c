/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:56:02 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/18 20:30:48 by frcastil         ###   ########.fr       */
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

	fd_in = open(argv[1], O_RDONLY, 777);
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

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 777);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		ft_error("Error in dup2\n");
	close(fd[1]);
	close(fd[0]);
	ft_execution(argv[3], envp);
}

void	ft_read_fd(int *fd_here, int fd)
{
	char	*new;

	new = malloc(10 + 1);
	read(fd_here[0], new, 10);
	printf ("POP: %s", new);
	fd = fd_here[0];
}

int	ft_get_fd_in(char **argv)
{
	int		fd;
	char	*str;
	int		fd_here[2];

	fd = 0;
	str = NULL;
	pipe(fd_here);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		while (1)
		{
			str = malloc(10 + 1);
			read(0, str, 10);
			if (ft_strncmp(str, argv[2], ft_strlen(argv[2]) - 1) == 0)
				break ;
			write(fd_here[1], str, ft_strlen(str));
			write(fd_here[1], "\n", 1);
			free(str);
		}
		close(fd_here[1]);
		ft_read_fd(&fd_here[0], fd);
	}
	else
		fd = open(argv[1], O_RDONLY, 777);
	return (fd);
}

int	main(int argc, char *argv[], char **envp)
{
	pid_t	pid;
	int		fd_infile;

	(void) pid;
	(void) envp;
	if (argc < 5)
	{
		ft_printf("Error\nExample: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		exit(EXIT_FAILURE);
	}
	fd_infile = ft_get_fd_in(argv);
	(void) fd_infile;
	return (0);
}
