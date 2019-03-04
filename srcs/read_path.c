/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:18:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 23:35:45 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*read_path(t_prgm *glob)
{
	char	*path;

	path = ft_strdup(ms_getenv(glob, glob->env, "PATH"));
	if (!path)
		path = get_path(glob);
	return (path);
}
