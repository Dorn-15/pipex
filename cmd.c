/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:54:41 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/21 16:07:30 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	char	*cmd_path;
	int		i;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_split(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	execute_cmd(char **cmd, char **env)
{
	char	*cmd_path;
	
	if (!cmd || !cmd[0])
	{
		perror("empty command");
		exit(errno);
	}
	cmd_path = find_path(cmd[0], env);
	if (!cmd_path)
	{
		perror("command not found");
		exit(errno);
	}
	execve(cmd_path, cmd, env);
	exit(1);
}
