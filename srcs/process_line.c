/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 04:17:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/13 01:59:31 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_prompt(t_prgm *glob)
{
	char	*path;

	path = ms_getenv(glob, &glob->env, "PWD");
	if (*path == '/' && path[1] == '\0')
		ft_putstr("[/] ");
	else
		ft_printf("[%s] ", ft_strrchr(path, '/') + 1);
}

int			process_line(t_prgm *glob)
{
	ft_freetab(&glob->tab.av);
	ft_bzero(&glob->tab, sizeof(t_tab));
	glob->status = 0;
	display_prompt(glob);
	if (ft_getdelim(0, &glob->line, '\n') != 1)
		glob->error = FAILED_READ;
	if (!glob->error)
	{
		replace_variable(glob);
		replace_home(glob);
		split_input(glob);
	}
	if (!glob->tab.ac && !glob->error)
		glob->error = EMPTY_LINE;
	ft_strdel(&glob->line);
	return (1);
}
