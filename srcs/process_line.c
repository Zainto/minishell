/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 04:17:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/27 18:20:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			process_line(t_prgm *glob)
{
	int		ret;

	ft_freetab(&glob->tab.av);
	ft_strdel(&glob->line);
	ft_putstr("$> ");
	ret = ft_getdelim(0, &glob->line, '\n');
	if (ret != 1)
		return (glob->error = FAILED_READ);
	split_input(glob);
	return (1);
}
