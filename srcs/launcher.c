/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:05:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/05 02:53:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include <sys/types.h>
#include <sys/wait.h>

int		launcher(t_prgm *glob, char *exec, char **env)
{
	pid_t		process;
	char		*variable;

	if (!access(exec, F_OK))
	{
		if ((process = fork()))
		{
			variable = NULL;
			waitpid(process, &glob->status, 0);
			if (!glob->status)
			{
				ft_asprintf(&variable, "_=%s", exec);
				variabletolist(glob, &glob->env, variable);
				ft_strdel(&variable);
			}
			return (glob->status);
		}
		else
			execve(exec, &glob->tab.av[glob->tab.id], env);
	}
	return (1);
}
