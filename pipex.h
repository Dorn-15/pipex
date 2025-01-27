/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:18:51 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/23 16:55:01 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/include/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

char	*find_path(char *cmd, char **env);
void	execute_cmd(char **cmd, char **env);

void	child_process1(int *fd, int *pipefd, char **cmd1, char **env);
void	child_process2(int *fd, int *pipefd, char **cmd2, char **env);
void	process1(int *fd, int *pipefd, char *cmd_str, char **env);
void	process2(int *fd, int *pipefd, char *cmd_str, char **env);

void	close_prog(int (*fd)[2], char **cmd1, char **cmd2);
void	close_pipes(int *fd, int *pipefd, pid_t pid);

# endif
