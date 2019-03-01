/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:05:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 04:38:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include <sys/types.h>
#include <sys/wait.h>

int		launcher(t_prgm *glob, t_status *exec, char **env)
{
	pid_t		process;

	if (!access(exec->path, F_OK))
	{
		if ((process = fork()))
		{
			waitpid(process, &glob->status, 0);
			return (0);
		}
		else
			execve(exec->path, glob->tab.av, env);
	}
	return (1);
}
