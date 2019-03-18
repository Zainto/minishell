/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:46:16 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/18 11:12:43 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void		delete_glob(t_prgm *glob)
{
	ft_lstdel(&glob->env, variable_delete);
	ft_freetab(&glob->tab.av);
	ft_strdel(&glob->line);
}

int				ms_exit(t_prgm *glob)
{
	int		exitcode;
	int		index;

	index = 0;
	if (glob->tab.ac > 2)
		return (glob->error = WRONG_EXIT_ARGS);
	if (glob->tab.ac > 1 && (glob->error <= -7 || glob->error == 0))
	{
		while (glob->tab.av[1][index])
			if (!ft_isdigit(glob->tab.av[1][index++]))
				return (glob->error = EXIT_INT);
		exitcode = ft_atoi(glob->tab.av[1]);
	}
	else if (glob->tab.ac == 1 && ft_strequ(glob->tab.av[0], "exit"))
		exitcode = 0;
	else
		exitcode = -1;
	delete_glob(glob);
	exit(exitcode);
	return (0);
}

int				echo(t_prgm *glob)
{
	int		n;
	int		i;

	i = 1;
	n = 0;
	if (ft_strequ(glob->tab.av[i], "-n"))
	{
		n = 1;
		i++;
	}
	while (i < glob->tab.ac && glob->tab.av[i])
		ft_printf("%s ", glob->tab.av[i++]);
	if (!n)
		ft_putchar('\n');
	return (0);
}

int				ms_unsetenv(t_prgm *glob)
{
	int		i;

	if (glob->tab.ac < 2)
		return (glob->error = TOO_FEW_ARGS);
	i = 1;
	while (glob->tab.av[i])
		ft_lstremove_if(&glob->env, glob->tab.av[i++], varcmp, variable_delete);
	return (0);
}
