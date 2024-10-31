/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:07:27 by antofern          #+#    #+#             */
/*   Updated: 2024/10/31 15:42:18 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//NO PROBADA
void args_error(void)
{
	write(1, "Incorrect number of arguments.\n"
	"Use ./pipex <infile> <command 1> <command 2> outfile", 84);
	exit(1);
}

//NO PROBADA
void infile_to_stdin(char *infile, char **env)
{
	int fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	
}

//NO PROBADA
void stdout_to_pipe(t_pipe *pip)
{
	if (pipe(pip)== -1 || dup2(pip[0], STDOUT_FILENO) == -1)
	{
		perror(NULL);
		exit(1);
	}
}

//NO PROBADA
void first_child(char *infile, char *cmd1, char **env, t_pipe *pip)
{
	pid_t	pid;

	stdout_to_pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		close(pip[1]);
		infile_to_stdin(infile, env);
		exec_cmd()

	}
	else
	{
		close(pip[0])
	}

	return (pipe);
}

//NO PROBADA
int	main(int argc, char **argv, char **env)
{
	/*Parser*/
	if (argc != 5)
		args_error();

	first_child(argc[1], argc[2], env);

	 /*last_child*/

	while (/*Esperar a cada proceso*/)
		wait();

	 /*Free_envPATH*/
}