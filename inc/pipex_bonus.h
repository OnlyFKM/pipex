/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:09:07 by frcastil          #+#    #+#             */
/*   Updated: 2023/11/27 16:58:26 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"

// main.c
int		main(int argc, char *argv[], char **envp);
int		ft_here_doc(char *argv[], int argc);
void	ft_here_process(int fd_here[2], char *argv[]);
void	ft_child_process(char *argv[], char **envp);
void	ft_parent_process(int fd_pipex[2]);

// utils.c
void	ft_error(char *text, int flag);
char	*ft_find_path(char **envp, char *command);
void	ft_execution(char *argv, char **envp);
char	*ft_joinslash(char *cmd);

#endif