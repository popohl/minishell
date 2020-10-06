/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:52 by paulohl           #+#    #+#             */
/*   Updated: 2020/10/06 10:33:14 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "../libft/libft.h"

t_commands	*create_link(char which_in)
{
	t_commands	*link;

	if (!(link = (t_commands *)malloc(sizeof(t_commands))))
		return (NULL);
	link->cmd_args = 0;
	link->which_in = which_in;
	link->next = 0;
	return (link);
}

char		*get_args(char *buffer, int i)
{
	char	*result;

	if (!(result = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	if (!(result = ft_strdup(buffer)))
		return (NULL);
	return (result);
}

t_commands	*quote_sensitive_split(char *buffer)
{
	t_commands	*commands;
	t_commands	*first;
	int			i;

	i = -1;
	if (buffer[i + 1] == 0)
		return (NULL);
	commands = create_link(';');
	first = commands;
	while (buffer[++i])
	{
		if (buffer[i] == '"')
			while (buffer[i] && buffer[i] != '"')
				i++;
		else if (buffer[i] == '\'')
			while (buffer[i] && buffer[i] != '\'')
				i++;
		else if (buffer[i] == '|' || buffer[i] == ';')
		{
			commands->next = create_link(buffer[i]);
			buffer[i] = 0;
			commands->cmd_args = get_args(buffer, i);
			commands = commands->next;
			buffer = buffer + i + 1;
			i = -1;
		}
	}
	commands->cmd_args = get_args(buffer, i);
	return (first);
}

int			parser(char *buffer)
{
	t_commands	*args;

	if (!(args = quote_sensitive_split(buffer)))
		return (1);
	while (args != 0)
	{
		printf("args->which_in: %c, args->cmd_args: %s\n", args->which_in, args->cmd_args);
		args = args->next;
	}
	return (0);
}
