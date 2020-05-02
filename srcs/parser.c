/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:52 by paulohl           #+#    #+#             */
/*   Updated: 2020/04/22 17:51:39 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "../libft/libft.h"

int		arg_count(char *buffer)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (buffer[i] && buffer[i] != ' ')
		count++;
	while (buffer[i])
	{
		if ((i != 0 && buffer[i] != ' ' && buffer[i - 1] == ' '))
			count++;
		if (buffer[i] == '"')
			while (buffer[++i] && buffer[i] != '"')
				;
		else if (buffer[i] == '\'')
			while (buffer[++i] && buffer[i] != '\'')
				i++;
		if (!buffer[i])
			return (-1);
		i++;
	}
	return (count);
}

char	**ft_argsplit(char *buffer)
{
	char	**args;

	if (!(args = (char **)malloc(sizeof(**args) * arg_count(buffer))))
		return (NULL);
	return (args);
}

int		parser(char *buffer)
{
	char	**args;

	if (!(args = ft_argsplit(buffer)))
		return (1);
	while (*args != 0)
	{
		DS(*args);
		args++;
	}
	return (0);
}
