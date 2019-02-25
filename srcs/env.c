/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/25 12:04:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_variable(t_list *node)
{
	t_variable	*variable;

	variable = (t_variable *)node->data;
	ft_printf ("%s=%s\n", variable->name, variable->data);
}

int		ms_env(t_prgm *glob)
{
	if(glob->tab.ac == 1)
	{
		ft_lstiter(glob->env, print_variable);	
		return (0);
	}
	return (0);
}
