/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:29 by paulohl           #+#    #+#             */
/*   Updated: 2020/10/06 10:04:33 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_CMD_LEN 262144

# include "debug.h"

typedef struct			s_commands {
	char				*cmd_args;
	char				which_in;
	struct s_commands	*next;
}						t_commands;

int		parser(char *buffer);

#endif
