/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitqu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:02:09 by antofern          #+#    #+#             */
/*   Updated: 2024/12/21 14:04:46 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/headers/libft.h"

static char	*ft_strndup(const char *src, int length)
{
	char	*new_string;
	int		i;

	new_string = (char *)malloc((length + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		new_string[i] = src[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

int	skipquotes(char **end, char **start)
{
	char	*tmp;
	char	q;

	if (**end == 39 || **end == '"')
	{
		q = **end;
		if (start && *start)
			(*start)++;
		tmp = *end;
		while (*tmp != '\0')
		{
			tmp++;
			if (*tmp == q)
			{
				*end = tmp;
				return (1);
			}
		}
		if (start && *start)
			(*start)--;
	}
	return (0);
}

static int	ft_count_substr(const char *str, char tkn)
{
	int	count;
	int	check;

	count = 0;
	while (*str != '\0')
	{
		check = 0;
		if (*str != tkn)
			check = 1;
		while (*str != tkn && *str != '\0')
		{
			skipquotes((char **)&str, NULL);
			str++;
		}
		while (*str == tkn && *str != '\0')
			str++;
		if (check == 1)
			count++;
	}
	return (count);
}

static int	delimit_next_str(char **next_str, char const **src_str, char tkn)
{
	int	quote;

	quote = 0;
	while (**src_str == tkn && **src_str != '\0')
	{
		(*src_str)++;
		(*next_str)++;
	}
	while (**next_str != tkn && **next_str != '\0')
	{
		quote = skipquotes(next_str, (char **)src_str);
		(*next_str)++;
	}
	return (quote);
}

static int	ft_to_chop(char **array_substr, int substring_count,
char const *src_str, char tkn)
{
	int		i;
	char	*next_str;
	int		quote;

	i = -1;
	next_str = (char *)src_str;
	while (++i < substring_count)
	{
		quote = delimit_next_str(&next_str, &src_str, tkn);
		if (quote == 1)
			array_substr[i] = ft_strndup(src_str, ((next_str - 1) - src_str));
		else
			array_substr[i] = ft_strndup(src_str, (next_str - src_str));
		if (array_substr[i] == NULL)
		{
			while (i >= 0)
				free(array_substr[i--]);
			return (1);
		}
		src_str = next_str;
	}
	return (0);
}

char	**ft_splitqu(char const *s, char c)
{
	int			substring_count;
	char		**array_substrings;
	const char	*copy_s;

	copy_s = s;
	if (!s)
		return (NULL);
	substring_count = ft_count_substr(copy_s, c);
	array_substrings = (char **)malloc((substring_count + 1) * sizeof(char *));
	if (array_substrings == NULL)
		return (NULL);
	array_substrings[substring_count] = NULL;
	if (ft_to_chop(array_substrings, substring_count, s, c) == 1)
	{
		free(array_substrings);
		return (NULL);
	}
	return (array_substrings);
}
