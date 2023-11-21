/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:56:02 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/21 14:00:24 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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
			str = get_next_line(0);
			if (ft_strncmp(str, argv[2], ft_strlen(argv[2]) + 1) == 10)
				break ;
			write(fd_here[1], str, ft_strlen(str));
			free(str);
		}
		close(fd_here[1]);
		ft_read_fd(&fd_here[0], fd);
		*argv += 3;
	}
	else
	{
		fd = open(argv[1], O_RDONLY, 777);
		*argv += 2;
	}
	return (fd);
}

/* void	ft_pipex(char *argv[], char **envp, int *fd_pipex, pid_t pid)
{
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
} */

int	main(int argc, char *argv[], char **envp)
{
	pid_t	pid;
	int		fd_infile;
/* 	int		i;
	int		fd_pipex[2]; */
	(void) envp;
	(void) pid;

	if (argc < 5)
	{
		ft_printf("Error\nExample: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		exit(EXIT_FAILURE);
	}
	fd_infile = ft_get_fd_in(argv);
	if (fd_infile == -1)
		exit(EXIT_FAILURE);
/* 	i = 0;
	while (argv[i] && i < argc -1)
	{
		ft_pipex(argv, envp, fd_pipex, pid);
		i++;
	} */
	return (0);
}
