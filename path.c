/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:39:57 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/22 20:49:15 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_path(char **envp)
{
	if (*envp == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/ \
				local/munki:/opt/X11/bin:/Library/Apple/usr/bin");
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	return (*envp + 5);
}

char	*get_cmd_path(t_data *pipex, char *cmd)
{
	char	*cmd_path;

	pipex->env_paths = ft_split(get_env_path(pipex->envp), ':');
	if (pipex->env_paths == NULL)
		free (pipex->env_paths);
	while (*pipex->env_paths != NULL)
	{
		*pipex->env_paths = ft_strjoin(*pipex->env_paths, "/");
		cmd_path = ft_strjoin(*pipex->env_paths, cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		pipex->env_paths++;
		free (cmd_path);
	}
	while (*pipex->env_paths != NULL)
		free (*pipex->env_paths);
	free (*pipex->env_paths);
	return (NULL);
}
