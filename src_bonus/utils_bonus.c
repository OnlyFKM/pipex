/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:32:58 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/23 15:44:52 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_error(char *text)
{
	perror(text);
	exit(EXIT_FAILURE);
}

char	*ft_find_path(char **envp, char *command)
{
	char	**tmp;
	char	**splited;
	char	*final_path;

	tmp = envp;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "PATH", 4) == 0)
			break ;
		tmp++;
	}
	splited = ft_split(*(tmp) + 5, ':');
	while (*splited)
	{
		final_path = ft_strjoin(*splited, command);
		if (access(final_path, F_OK) == 0)
			return (final_path);
		splited++;
	}
	return (ft_printf("Error\nCommand not found!"), NULL);
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

void	ft_read_fd(int *fd_here)
{
	char	*new;

	new = get_next_line(fd_here[0]);
	while (new)
	{
		ft_printf ("HERE_DOC: %s", new);
		new = get_next_line(fd_here[0]);
	}
}

/* int	ft_get_fd_in(char **argv)
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
		//argv += 3;
	}
	else
	{
		fd = open(argv[1], O_RDONLY, 777);
		argv += 2;
	}
	return (fd);
} */