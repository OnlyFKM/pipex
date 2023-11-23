/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:56:02 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/23 18:40:47 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_child_process(char *argv[], char **envp)
{
	pid_t	pid;
	int		fd_pipex[2];

	if (pipe(fd_pipex) < 0)
		ft_error("Error");
	pid = fork();
	if (pid == -1)
		ft_error("Error");
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
	char	*str;
	int		fd_here[2];

	if (argc > 5)
	{
		if (pipe(fd_here) < 0)
			return (-1);
		while (1)
		{
			str = get_next_line(0);
			if (ft_strncmp(str, argv[2], ft_strlen(argv[2]) + 1) == 10)
				break ;
			write(fd_here[1], str, ft_strlen(str));
			free(str);
		}
		free(str);
		close(fd_here[1]);
		return (fd_here[0]);
	}
	else
	{
		ft_printf("Error\nWrong number of argues\n");
		exit(EXIT_FAILURE);
	}
}

int	ft_type_of_infile(char *argv[], int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (ft_here_doc(argv, argc));
	return (open(argv[1], O_RDONLY));
}

int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	if (argc >= 5)
	{
		infile = ft_type_of_infile(argv, argc);
		if (infile == -1)
			ft_error("Error");
		//close(infile);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(infile, STDIN_FILENO);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			i = 3;
		else
			i = 2;
		while (i < argc - 2)
			ft_child_process(&argv[i++], envp);
		dup2(outfile, STDOUT_FILENO);
		ft_execution(argv[argc - 2], envp);
	}
	return (0);
}
