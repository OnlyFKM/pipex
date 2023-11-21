/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:47:24 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/20 13:11:54 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

// main.c
int		main(int argc, char *argv[], char **envp);
void	ft_child_process(char *argv[], char **envp, int *fd);
void	ft_parent_process(char *argv[], char **envp, int *fd);
int		ft_get_fd_in(char **argv);

// utils.c
void	ft_error(char *text);
char	*ft_find_path(char **envp, char *command);
void	ft_execution(char *argv, char **envp);
char	*ft_joinslash(char *cmd);
void	ft_read_fd(int *fd_here, int fd);

#endif