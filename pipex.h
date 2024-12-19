/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:32:42 by antofern          #+#    #+#             */
/*   Updated: 2024/12/19 17:13:36 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include "libft/headers/libft.h"

typedef int t_pipe[2];

void	exec_cmd(int index_arg, char **argv, char **env);
char	**ft_splitqu(char const *s, char c);

#endif