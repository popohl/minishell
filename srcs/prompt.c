/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:25 by paulohl           #+#    #+#             */
/*   Updated: 2020/10/06 09:46:19 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "../libft/libft.h"

int		print_prompt(char *buf)
{
	int		n;

	write(1, "$> ", 3);
	n = read(0, buf, MAX_CMD_LEN);
	buf[n - 1] = 0;
	if (n == MAX_CMD_LEN)
		return (0);
	return (n);
}

int		main(void)
{
	char	*buf;

	if (!(buf = (char *)malloc(sizeof(*buf) * MAX_CMD_LEN)))
		return (1);
	while (1)
	{
		if (!print_prompt(buf))
			return (2);
		while (is_whitespace(*buf))
			buf++;
		if (parser(buf))
			return (3);
	}
	return (0);
}
