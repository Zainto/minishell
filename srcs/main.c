/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/27 18:34:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void		destruction(t_prgm *glob)
{
	ft_lstdel(&glob->env, variable_delete);
	ft_dirdel(&glob->exec);
	ft_freetab(&glob->tab.av);
	ft_strdel(&glob->line);
}

int			main(int ac, char **av, char **env)
{
	t_prgm		glob;

	if (ac > 1)
		return (0);
	(void)av;
	if (!initialization(&glob, env))
	{
		while (process_line(&glob))
		{
			if (!builtins_exec(&glob) || !launcher(&glob))
				continue;
			else
				error_manager(&glob);
		}
	}
	destruction(&glob);
	return (0);
}
