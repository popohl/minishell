/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:52 by paulohl           #+#    #+#             */
/*   Updated: 2020/10/06 11:40:44 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "../libft/libft.h"

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
** get_args only creates a string for the moment, but it will have the task of
** separating each argument into separate words to be sent to execve.
** It will return a char** instead of a char*.
** It may have the task of detecting '<', '>' and '>>' but not sure yet.
*/

char		*get_args(char *buffer, int i)
{
	char	*result;

	if (!(result = ft_strdup(buffer)))
		return (NULL);
	return (result);
}

/*
** save_link saves the command inside the current link's cmd_args and
** creates a new link with create_link.
** It then resets buffer and i's values to continue reading the line.
*/

t_commands	*save_link(t_commands *command, char **buffer, int *i)
{
	printf("%c\n", buffer[0][*i]);
	command->next = create_link(buffer[0][*i]);
	buffer[0][*i] = 0;
	command->cmd_args = get_args(*buffer, *i);
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
	if (buffer[i + 1] == 0)
		return (create_link(';'));
	if (!(command = create_link(';')))
		return (NULL);
	first = command;
	while (buffer[++i])
	{
		if (buffer[i] == '"' && (++i != -1))
			while (buffer[i] && buffer[i] != '"')
				i++;
		else if (buffer[i] == '\'' && (++i != -1))
			while (buffer[i] && buffer[i] != '\'')
				i++;
		else if (buffer[i] == '|' || buffer[i] == ';')
			if (!(command = save_link(command, &buffer, &i)))
				return (NULL);
	}
	command->cmd_args = get_args(buffer, i);
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
