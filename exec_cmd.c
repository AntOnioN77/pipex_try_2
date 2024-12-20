/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:54:20 by antofern          #+#    #+#             */
/*   Updated: 2024/12/20 23:03:47 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <linux/limits.h>

void	free_split(char **ch_chain)
{
	int i;

	i = 0;
	while (ch_chain[i])
	{
		free(ch_chain[i]);
		i++;
	}
	free(ch_chain);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	if (envp == NULL)
		return (NULL);
	i = -1;
	paths = NULL;
	while(envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(&(envp[i][5]), ':');
			if(*paths == NULL || **paths == '\0')
				return (NULL);
			break;
		}
	}
	return (paths);
}

//Escribe en el buffer pathname la primera ruta+comando valida para ejecucion que encuentre. 
//si no encuentra ruta valida retorna 1
static int	path_selector(char *pathname, char **paths, char *command)
{
	int i;

	if (pathname == NULL || paths == NULL || command == NULL)
		return (1);
	i = -1;
	while(paths[++i] != NULL)
	{
		ft_strlcpy(pathname, paths[i], PATH_MAX);
		ft_strlcat(pathname, "/", PATH_MAX);
		ft_strlcat(pathname, command, PATH_MAX);
		if(access(pathname, X_OK) == 0)
			return (0);
	}
	return (127);
}

//LA funcion llamadora debera mostrar el codigo de errno en caso de que esta funcion retorne null
//trata de implementar un buffer donde se concatene el path+/+comando en lugar de mallocear tanto
static int find_path(char **env, char *command, char *pathname)
{
	char **paths;
	int path_return;

	if(command && (access(command, X_OK) == 0))
	{
		ft_strlcpy(pathname, command, PATH_MAX);
		return (0);
	}
	paths = get_paths(env);
	path_return = path_selector(pathname, paths, command);
	if (path_return == 0)
	{
		free_split(paths);
		return (0);
	}
	//ft_putstr_fd("pipex: ", 2);
	//ft_putstr_fd(command, 2);
	if (paths == NULL)
		ft_putstr_fd("pipex: No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	//perror(command);
	//ft_putstr_fd(strerror(ENOENT), 2);
	free_split(paths);
	return (path_return);
}

void	exec_cmd(int index_arg, char **argv, char **env)
{
	char pathname[PATH_MAX];
	char **cmdflags;
	int path_return;

	cmdflags = ft_splitqu(argv[index_arg], ' ');
//printarray(cmdflags);
	if (cmdflags == NULL)
		exit (1);
	path_return = find_path(env, cmdflags[0], pathname);
	if (path_return != 0)
	{
		free_split(cmdflags);
		exit (path_return);
	}
	execve(pathname, cmdflags, env);
	exit (1);
}