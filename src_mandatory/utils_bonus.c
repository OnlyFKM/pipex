/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:32:58 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/18 17:54:22 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
	return (ft_error("Error\nCommand not found!"), NULL);
}
