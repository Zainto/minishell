/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execinit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 02:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 08:24:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <fcntl.h>

int		ExecListGenerated(void)
{
	t_prgm	glob;

	glob_test_init(&glob);
	if(execinit(&glob) == 0)
	{
		glob_test_destructor(&glob);
		return (ISTRUE);
	}
	return (ISFALSE);
}

int		test_execinit(void)
{
	t_stack tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "EXECINIT");
	load_test(&tests,"Exec list is Correctly Generated", ExecListGenerated);
	return (run_test(&tests));
}
