/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execinit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 02:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/25 04:27:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <fcntl.h>

int		GenerateExecList(void)
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
	load_test(&tests,"Generate Full Executable List", GenerateExecList);
	return (run_test(&tests));
}