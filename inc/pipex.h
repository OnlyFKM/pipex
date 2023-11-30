/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:47:24 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/28 11:36:43 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

// main.c
int		main(int argc, char *argv[], char **envp);
void	ft_child_process(char *argv[], char **envp, int *fd);
void	ft_parent_process(char *argv[], char **envp, int *fd);

// utils.c
void	ft_error(char *text, int flag);
char	*ft_find_path(char **envp, char *command);
void	ft_execution(char *argv, char **envp);
char	*ft_joinslash(char *cmd);

#endif