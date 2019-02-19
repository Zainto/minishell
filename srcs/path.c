/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:18:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/19 00:47:07 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		print_exec(t_list *node)
{
	t_status	*file;

	file = (t_status *)node->data;
	ft_printf("%s\n", file->name);
}
