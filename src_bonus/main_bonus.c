/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:56:02 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/27 17:24:12 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_child_process(char *argv[], char **envp)
{
	pid_t	pid;
	int		fd_pipex[2];

	if (pipe(fd_pipex) < 0)
		ft_error("Error", 1);
	pid = fork();
	if (pid == -1)
		ft_error("Error", 1);
	if (pid == 0)
	{
		close(fd_pipex[0]);
		dup2(fd_pipex[1], STDOUT_FILENO);
		ft_execution(*argv, envp);
	}
	else
		ft_parent_process(fd_pipex);
}

void	ft_parent_process(int fd_pipex[2])
{
	close(fd_pipex[1]);
	dup2(fd_pipex[0], STDIN_FILENO);
	wait(0);
}

int	ft_here_doc(char *argv[], int argc)
{
	int		fd_here[2];
	pid_t	id;

	if (argc == 5)
		ft_error("Error\nWrong number of arguments\n", 2);
	if (pipe(fd_here) < 0)
		return (-1);
	id = fork();
	if (id < 0)
		return (-1);
	if (id == 0)
		ft_here_process(fd_here, argv);
	else
	{
		close(fd_here[1]);
		ft_parent_process(fd_here);
	}
	return (fd_here[0]);
}

void	ft_here_process(int fd_here[2], char *argv[])
{
	char	*str;

	close(fd_here[0]);
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(str, argv[2], ft_strlen(argv[2]) + 1) == 10)
		{
			free(str);
			break ;
		}
		write(fd_here[1], str, ft_strlen(str));
		free(str);
	}
	close(fd_here[1]);
	exit(0);
}

int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		{
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 777);
			ft_here_doc(argv, argc);
			i = 3;
		}
		else
		{
			infile = open(argv[1], O_RDONLY, 777);
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 777);
			dup2(infile, STDIN_FILENO);
			i = 2;
		}
		while (i < argc - 2)
			ft_child_process(&argv[i++], envp);
		dup2(outfile, STDOUT_FILENO);
		ft_execution(argv[argc - 2], envp);
	}
	return (0);
}
