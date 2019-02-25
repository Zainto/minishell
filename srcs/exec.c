/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:00:02 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/21 22:33:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_exec(t_prgm *glob, char *name)
{
	(void)glob;
	if (!name)
		return (NULL_ARG);
	return (0);
}
