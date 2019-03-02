/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:05:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/02 03:06:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include <sys/types.h>
#include <sys/wait.h>

int		launcher(t_prgm *glob, char *exec, char **env)
{
	pid_t		process;

	if (!access(exec, F_OK))
	{
		if ((process = fork()))
		{
			waitpid(process, &glob->status, 0);
			return (glob->status);
		}
		else
			execve(exec, &glob->tab.av[glob->tab.id], env);
	}
	return (1);
}
