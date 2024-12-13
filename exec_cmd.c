/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:54:20 by antofern          #+#    #+#             */
/*   Updated: 2024/12/13 15:02:36 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <assert.h>//BORRAR

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
			assert(paths != NULL); //////////////prueba
			if(paths == NULL)
				return (NULL);
			break;
		}
	}
	//TO DO: No solo notificar, tambien liberar lo que sea preciso
	if (envp[i] == NULL)
	{
		free_split(paths);
		write(1, "variable PATH no encontrada\n", 28);
	}
	//fin prueba
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
		ft_strlcpy(pathname, paths[i], 1024);
		ft_strlcat(pathname, "/", 1024);
		ft_strlcat(pathname, command, 1024);
		if(access(pathname, X_OK) == 0)
			return (0);
	}
	return (1);
}

//LA funcion llamadora debera mostrar el codigo de errno en caso de que esta funcion retorne null
//trata de implementar un buffer donde se concatene el path+/+comando en lugar de mallocear tanto
static int find_path(char **env, char *command, char *pathname)
{
	char **paths;

	if(access(command, X_OK) == 0)
	{
		ft_strlcpy(pathname, command, 1024);
		return (0);
	}
	paths = get_paths(env);
	if (paths == NULL)
		return (1);
	if (path_selector(pathname, paths, command) == 0)
	{
		free_split(paths);
		return (0);
	}
	ft_putstr_fd("pipex: ", 2);
	perror(command);
	//ft_putstr_fd(strerror(ENOENT), 2);
	free_split(paths);
	return (1);
}

void printarray(char **arr) //funcion de prueba, borrar
{
	int i = 0;
	while(arr[i])
	{
		fprintf(stderr,"%s\n", arr[i]);
		i++;
	}
}

void	exec_cmd(int index_arg, char **argv, char **env)
{
	char pathname[1024];
	char **cmdflags;

	cmdflags = ft_splitqu(argv[index_arg], ' ');
//printarray(cmdflags);
	if (cmdflags == NULL)
		exit (1);
	if (find_path(env, cmdflags[0], pathname) == 1)
	{
		free_split(cmdflags);
		exit (1);
	}
	execve(pathname, cmdflags, env);
	exit (1);
}