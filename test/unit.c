/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:41:04 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 01:14:54 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

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

void	generate_test_dir(void)
{
	int		fd;

	mkdir("/tmp/minishell_test", T_CHMOD);
	fd = open("/tmp/minishell_test/exe", O_CREAT + O_TRUNC);
	close(fd);
}

void	glob_test_init(t_prgm *glob)
{
	t_variable 	variable1= {.name = "toti", .data = "tatf"};
	t_variable	variable2= {.name = "totp", .data = "tata"};
	t_variable	variable3= {.name = "totl", .data = "tatv"};
	t_variable	variable4= {.name = "totm", .data = "tatb"};
	t_variable	variable5= {.name = "totn", .data = "tatn"};
	t_variable	variable6= {.name = "PATH", .data = ENV_PATH};
	t_variable	variable7= {.name = "HOME", .data = HOME};

	ft_bzero(glob, sizeof(t_prgm));
	ft_lstadd(&glob->env, ft_lstnew(&variable1, sizeof(t_variable)));
	ft_lstadd(&glob->env, ft_lstnew(&variable2, sizeof(t_variable)));
	ft_lstadd(&glob->env, ft_lstnew(&variable3, sizeof(t_variable)));
	ft_lstadd(&glob->env, ft_lstnew(&variable4, sizeof(t_variable)));
	ft_lstadd(&glob->env, ft_lstnew(&variable5, sizeof(t_variable)));
	ft_lstadd(&glob->env, ft_lstnew(&variable6, sizeof(t_variable)));
	ft_lstadd(&glob->env, ft_lstnew(&variable7, sizeof(t_variable)));
}

void	glob_test_destructor(t_prgm *glob)
{
	ft_lstdel(&glob->env, NULL);
	ft_lstdel(&glob->exec, NULL);
}

int		main(void)
{
	print_head();
	test_envinit();
	print_test_separator();	
	test_ms_getenv();
	print_test_separator();	
	test_read_path();
	print_test_separator();	
	test_generate_exec();
	print_test_separator();	
	test_execinit();
	print_test_separator();	
	test_line_processing();
	print_test_separator();	
	test_replace_variable();
	print_test_separator();	
	test_replace_home();
}
