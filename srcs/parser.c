/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:52 by paulohl           #+#    #+#             */
/*   Updated: 2020/10/08 13:31:59 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "../libft/libft.h"

int			skip_quote(char *buffer, int i)
{
	char	to_skip;

	to_skip = buffer[i];
	i++;
	while (buffer[i] && buffer[i] != to_skip)
		i++;
	return (i);
}

int			arg_count(char *args)
{
	int		i;
	int		count;

	i = 0;
	while (args && args[i] == ' ')
		i++;
	if (!args || !args[i])
		return (0);
	count = 1;
	while (args[i])
	{
		if ((args[i] == '>' && args[i + 1] == '>' && (++i != -1)) ||
				args[i] == '>' || args[i] == '<')
		{
			while (args[i + 1] == ' ')
				i++;
			if (args[i + 1] == '"' || args[i + 1] == '\'')
				i = skip_quote(args, i + 1) + 1;
			else
				while (args[i + 1] && args[i + 1] != ' ')
					i++;
		}
		else if (i > 0 && args[i] != ' ' && args[i - 1] == ' ')
			count++;
		if (args[i] && (args[i] == '"' || args[i] == '\''))
			i = skip_quote(args, i);
		if (args[i])
			i++;
	}
	return (count);
}

/*
** create_link creates a link for the t_commands linked list.
** it then initializes the values.
** the character 'which_in' indicates whether command takes in a redirection,
** it can have the values: ';' (no redirection), '|' (pipe) and '<' (file input)
*/

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

/*
** save_link saves the command inside the current link's cmd_args and
** creates a new link with create_link.
** It then resets buffer and i's values to continue reading the line.
*/

t_commands	*save_link(t_commands *command, char **buffer, int *i)
{
	command->next = create_link(buffer[0][*i]);
	buffer[0][*i] = 0;
	while (buffer[0][0] == ' ')
	{
		(*buffer)++;
		(*i)--;
	}
	if (!(command->cmd_args = ft_strdup(*buffer)))
		return (NULL);
	*buffer = *buffer + *i + 1;
	*i = -1;
	return (command->next);
}

/*
** quote_sensitive_split splits the string by the characters ';' and '|' but
** it ignores anything between single and double quotes.
** Each splitted string is stored in a linked list 't_commands'.
*/

t_commands	*quote_sensitive_split(char *buffer)
{
	t_commands	*command;
	t_commands	*first;
	int			i;

	i = -1;
	if (buffer[0] == 0)
		return (create_link(';'));
	if (!(command = create_link(';')))
		return (NULL);
	first = command;
	while (buffer[++i])
	{
		if (buffer[i] == '"' || buffer[i] == '\'')
			i = skip_quote(buffer, i);
		else if (buffer[i] == '|' || buffer[i] == ';')
			if (!(command = save_link(command, &buffer, &i)))
				return (NULL);
	}
	while (*buffer == ' ')
		buffer++;
	if (!(command->cmd_args = ft_strdup(buffer)))
		return (NULL);
	return (first);
}

int			parser(char *buffer)
{
	t_commands	*args;
	int			argc;
	char		**argv;

	if (!(args = quote_sensitive_split(buffer)))
		return (1);
	while (args != 0)
	{
		// printf("args->which_in: %c, args->cmd_args: %s\n", args->which_in, args->cmd_args);
		argc = arg_count(args->cmd_args);
		printf("cmd_args: {%s}, argc: ", args->cmd_args);
		DD(argc);
		args = args->next;
		argc = 0;
		argv = 0;
	}
	return (0);
}
