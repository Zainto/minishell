/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/13 06:50:32 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int		duplicate_av(t_prgm *glob, int ac, char **av)
{
	int			index;
	int			id;

	id = 0;
	index = 1;
	if (!(glob->tab.av = malloc(sizeof(char *) * (ac))))
		return (glob->error = FAILED_MALLOC);
	while (index < ac)
		glob->tab.av[id++] = ft_strdup(av[index++]);
	glob->tab.av[id] = NULL;
	glob->tab.ac = ac - 1;
	return (0);
}

static void		non_interactive(t_prgm *glob, int ac, char **av)
{
	duplicate_av(glob, ac, av);
	replacer(glob);
	if (env_handeler(glob))
		error_manager(glob);
	ft_lstdel(&glob->env, variable_delete);
	ft_freetab(&glob->tab.av);
	ft_dirdel(&glob->exec);
}

static void		interactive(t_prgm *glob)
{
	while (process_line(glob))
	{
		if (glob->error)
			error_manager(glob);
		else if (env_handeler(glob))
			error_manager(glob);
	}
}

int				main(int ac, char **av, char **env)
{
	t_prgm		glob;

	if (!initialization(&glob, env))
	{
		if (ac > 1)
			non_interactive(&glob, ac, av);
		else
			interactive(&glob);
	}
	return (0);
}
