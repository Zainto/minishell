/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:41:04 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 08:20:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

void	print_head(void)
{
	ft_printf("%@s", "180", "--------------------------TESTS RESULTS");
	ft_printf("%@s", "180", "-----------------------------\n");
}

void	print_test_separator(void)
{
	ft_printf("%@s", "180", "----------------------------------");
	ft_printf("%@s", "180", "----------------------------------\n");
}

void	glob_test_init(t_prgm *glob)
{
	t_env	variable1= {.name = "toti", .data = "tatf"};
	t_env	variable2= {.name = "totp", .data = "tata"};
	t_env	variable3= {.name = "totl", .data = "tatv"};
	t_env	variable4= {.name = "totm", .data = "tatb"};
	t_env	variable5= {.name = "totn", .data = "tatn"};
	t_env	variable6= {.name = "PATH", .data = "ENV_PATH"};

	ft_bzero(glob, sizeof(t_prgm));
	ft_lstadd(&glob->env, ft_lstnew(&variable1, sizeof(t_env)));
	ft_lstadd(&glob->env, ft_lstnew(&variable2, sizeof(t_env)));
	ft_lstadd(&glob->env, ft_lstnew(&variable3, sizeof(t_env)));
	ft_lstadd(&glob->env, ft_lstnew(&variable4, sizeof(t_env)));
	ft_lstadd(&glob->env, ft_lstnew(&variable5, sizeof(t_env)));
	ft_lstadd(&glob->env, ft_lstnew(&variable6, sizeof(t_env)));
}

void	glob_test_destructor(t_prgm *glob)
{
	ft_lstdel(&glob->args, NULL);
	ft_lstdel(&glob->env, NULL);
	ft_lstdel(&glob->exec, NULL);
	ft_strdel(&glob->line);
}

int		main(void)
{
	print_head();
	test_envinit();
	print_test_separator();	
	test_ft_getenv();
	print_test_separator();	
	test_get_path();
	print_test_separator();	
	test_execinit();
}
