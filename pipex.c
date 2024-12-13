/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:07:27 by antofern          #+#    #+#             */
/*   Updated: 2024/12/13 15:05:15 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "trace_tools/trace_tools.h"

//NO PROBADA
void	args_error(void)
{
	write(1, "Incorrect number of arguments.\n"
		"Use ./pipex <infile> <command 1> <command 2> outfile", 84);
	exit(1);
}

//NO PROBADA
void	infile_to_stdin(char *infile)
{
	int fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(infile);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(infile);
		exit(1);
	}
	close(fd);
}

void stdout_to_outfile(char *outfile)
{
	int fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 00664);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(outfile);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(outfile);
		exit(1);
	}
	close(fd);
	
}

//NO PROBADA
//dirige stdout hacia pipe[0] (extremo de lectura)
void stdout_to_pipe(t_pipe pip)
{
	if (dup2(pip[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(NULL);
		exit(1);
	}
	close(pip[1]);
}

//NO PROBADA
void first_child(char **argv, char **env, t_pipe pip)
{
	pid_t	pid;

	if (pipe(pip)== -1)
	{
		perror(NULL);
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		infile_to_stdin(argv[1]);
		stdout_to_pipe(pip);
		close(pip[0]);
		exec_cmd(2, argv, env);
	}
	else
	{
		close(pip[1]);
	}

	return ;
}

void last_child(char **argv, char **env, t_pipe pip)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(pip[0], STDIN_FILENO) == -1)
		{
			perror(NULL);
			exit(1);
		}
		close(pip[0]);
//		close(pip[1]);
		stdout_to_outfile(argv[4]);
		exec_cmd(3, argv, env);	
	}
	else
	{
		close(pip[0]);
	}
}

//NO PROBADA
int	main(int argc, char **argv, char **env)
{
	t_pipe	pip;
	int i;
	int status;

	if (argc != 5)
		args_error();
	first_child(argv, env, pip);
	last_child(argv, env, pip);

	i = 0;
	while (i++ < 2)
		wait(&status);
	 return (WEXITSTATUS(status));
}