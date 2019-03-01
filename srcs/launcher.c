/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:05:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/28 18:35:28 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int		find_exec(void *data, void *to_find)
{
	t_status *exec;

	exec = data;
	return (ft_strequ(exec->name, (char *)to_find));
}

char	**lsttotab(t_list *list)
{
	char		**tab;
	int			index;
	int			lstlen;
	t_variable	*tmp;

	lstlen = ft_lstlen(list);
	index = 0;
	tab = malloc(sizeof(char *) * (lstlen + 1));
	ft_bzero(tab, sizeof(char *) * (lstlen + 1));
	while (index < lstlen)
	{
		tmp = list->data;
		ft_asprintf(&tab[index++], "%s=%s",tmp->name, tmp->data);
	}
	tab[index] = NULL;
	return (tab);
}

int		launcher(t_prgm *glob)
{
	char		**env;
	t_list		*node;
	t_status	*exec;
	pid_t		process;

	if ((node = ft_lstfind(glob->exec, glob->tab.av[0], find_exec)))
	{
		exec = node->data;
		if (!access(exec->path, F_OK))
		{
			env = lsttotab(glob->env);
			if ((process = fork()))
			{
				waitpid(process, &glob->status, 0);
				ft_freetab(&env);
				return (0);
			}
			else
				execve(exec->path, glob->tab.av, env);
		}
	}
	return (1);
}
