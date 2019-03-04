/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 01:44:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 20:37:25 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static int	construct_exit(t_prgm *glob, int result)
{
	if (result == 0)
		return (1);
	glob->error = FAILED_MALLOC;
	return (0);
}

char		*get_home(void)
{
	struct passwd	*uid;
	uid_t			id;
	char			*home;

	home = NULL;
	id = getuid();
	uid = getpwuid(id);
	if (ft_asprintf(&home, "HOME=%s", uid->pw_dir) < 0)
		return (NULL);
	return (home);
}

static char	*construct_path(t_prgm *glob, int fd, char *previous)
{
	char	*tmp;
	char	*path;
	int		result;

	if ((result = ft_getdelim(fd, &tmp, '\n')) <= 0)
		return (construct_exit(glob, result) ? previous : NULL);
	path = NULL;
	ft_asprintf(&path, "%s%s:", previous ? previous : "", tmp);
	if (!path)
	{
		glob->error = FAILED_MALLOC;
		return (NULL);
	}
	ft_strdel(&previous);
	ft_strdel(&tmp);
	return (construct_path(glob, fd, path));
}

char		*get_path(t_prgm *glob)
{
	int		fd;
	char	*path;

	if ((fd = open(DEFAULT_PATH, O_RDONLY)) < 0)
	{
		glob->error = FAILED_OPEN;
		return (NULL);
	}
	path = construct_path(glob, fd, NULL);
	if (close(fd) == -1)
		glob->error = FAILED_CLOSE;
	return (path);
}

char		*ms_getenv(t_prgm *glob, char *name)
{
	t_list		*node;

	if (!name || !glob->env)
	{
		glob->error = NULL_ARG_PASSED;
		return (NULL);
	}
	if ((node = ft_lstfind(glob->env, name, varcmp)))
		return (((t_variable *)node->data)->data);
	return (NULL);
}
