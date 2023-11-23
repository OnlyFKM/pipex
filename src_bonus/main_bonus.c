/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:56:02 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/23 15:49:51 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/* void	ft_child_process(char *argv[], char **envp)
{
}

void	ft_parent_process(char *argv[], char **envp)
{
} */

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

int	ft_type_of_infile(char *argv[], int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (ft_here_doc(argv, argc));
	return (open(argv[1], O_WRONLY));
}

int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	//int	outfile;
	int	i;
	(void) envp;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			i = 3;
		else
			i = 2;
		infile = ft_type_of_infile(argv, argc);
		if (infile == -1)
			ft_error("Error");
		close(infile);
	}
	return (0);
}
