/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:54:20 by antofern          #+#    #+#             */
/*   Updated: 2024/10/31 15:44:14 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	path_selector(char *pathname, char **paths, char *command)
{
	int i;

	i = -1;
	while(paths[++i] != NULL)
	{
		ft_strlcpy(pathname, paths[i], 1024);
		ft_strlcat(pathname, "/", 1024);
		ft_strlcat(pathname, command, 1024);
		if(access(pathname, X_OK) == 0)
		{
			free_split(paths);
			return (0);
		}
	}
	return (1);
}

//LA funcion llamadora debera mostrar el codigo de errno en caso de que esta funcion retorne null
//trata de implementar un buffer donde se concatene el path+/+comando en lugar de mallocear tanto
int find_path(char **envp, char *command, char *pathname)
{
	char **paths;
	size_t len;

	if(access(command, X_OK) == 0)
	{
		ft_strlcpy(pathname, command, 1024);
		return (0);
	}
	paths = get_paths(envp);
	if (paths == NULL)
		return (1);
	if (path_selector(pathname, paths, command) == 0)
		return (0);
	ft_putstr_fd(strerror(ENOENT), 2);
	free_split(paths);
	return (1);
}

void	exec_cmd(int narg, char **argv, char **envp)
{
	char pathname[1024];
	char **cmdflags;

	cmdflags = ft_split(argv[narg], ' ');
	if (cmdflags == NULL)
		exit (1);
	if (find_path(envp, cmdflags[0], pathname) == 1)
	{
		free_split(cmdflags);
		exit (1);
	}
	execve(pathname, cmdflags, envp);
	exit (1);
}