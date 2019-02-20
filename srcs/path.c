/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:18:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 07:47:42 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	construct_exit(t_prgm *glob, int result)
{
	if (result == 0)
		return (1);
	glob->error = FAILED_MALLOC;
	return (0);
}

static char	*construct_path(t_prgm *glob, int fd, char *previous)
{
	char	*tmp;
	char	*path;
	int		result;

	if ((result = ft_getdelim(fd, &tmp, '\n')) <= 0)
		return (construct_exit(glob, result)? previous : NULL);
	path = NULL;
	ft_asprintf(&path,"%s%s:", previous ? previous : "", tmp);
	if (!path)
	{
		glob->error = FAILED_MALLOC;	
		return (NULL);
	}
	ft_strdel(&previous);
	ft_strdel(&tmp);
	return (construct_path(glob, fd, path));
}

static char	*load_path(t_prgm *glob)
{
	int		fd;
	char	*path;

	if ((fd = open(DEFAULT_PATH, O_RDONLY)) < 0)
	{
		glob->error = FAILED_OPEN;
		return (NULL);
	}
	path = construct_path(glob, fd, NULL);
	if(close(fd) == -1)
		glob->error = FAILED_CLOSE;
	return (path);
}

char	*get_path(t_prgm *glob)
{
	char	*path;

	path = ft_getenv(glob, "PATH");	
	if (!path)
		path = load_path(glob);
	return (path);
}

/*
   t_list		*generate_path(t_prgm *glob)
   {
   t_list		*execs;
   char		**paths;
   int			i;

   i = 0;
   execs = NULL;
   paths = ft_strsplit(ft_getenv(glob->env, "PATH"), ":");
   while (paths[i])
   {
   ft_dirlist(&execs, paths[i]);
   i++;
   }
   return (execs);
   }
   */
void		print_exec(t_list *node)
{
	t_status	*file;

	file = (t_status *)node->data;
	ft_printf("%s\n", file->name);
}
