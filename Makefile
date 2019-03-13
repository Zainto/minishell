# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 23:18:40 by cempassi          #+#    #+#              #
#    Updated: 2019/03/13 03:56:16 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAMEDB = minishelldb
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libftdb.a

CC = Clang
CCD = Clang -g3
COMPILE = $(CC) -c
DEBUG = $(CC) -g3 -c

# Reset
NC = \033[0m

# Regular Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
MKDIR = mkdir -p
CLEANUP = rm -rf

WFLAGS += -Wall
WFLAGS += -Werror
WFLAGS += -Wextra
DFLAGS = -fsanitize=address
IFLAGS = -I $(IPATH) -I $(LIPATH)
CFLAGS = $(WFLAGS)

OPATH = obj/
SPATH = srcs/
IPATH = includes/
LPATH = libft/
LIPATH = libft/includes/

INCS += minishell.h

SRCM += main.c

SRCS += basic_setup.c
SRCS += builtin.c
SRCS += change_directory.c
SRCS += env.c
SRCS += env_options.c
SRCS += error.c
SRCS += finders.c
SRCS += init.c
SRCS += get.c
SRCS += launcher.c
SRCS += process_line.c
SRCS += setunsetenv.c
SRCS += split_input.c
SRCS += replace.c

DSYM += $(NAME).dSYM
DSYM += $(NAMEDB).dSYM

OBJM = $(patsubst %.c, $(OPATH)%.o, $(SRCM))
OBJMD = $(patsubst %.c, $(OPATH)db%.o, $(SRCM))
OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(SRCS))

vpath %.c srcs
vpath %.h includes

all : $(NAME)

run : $(NAME)
	./$<
	
debug : $(NAMEDB)
	./$<

#Normal compilation
$(NAME): $(LIB) $(OPATH) $(OBJM) $(OBJS) $(INCS)
	$(CC) -o $@ $(LIB) $(OBJS) $(OBJM)
	printf "$(GREEN)$@ is ready.\n$(NC)"
	
$(OBJS) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(BLUE)Compiling $<\n$(NC)"

$(OBJM) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(BLUE)Compiling $<\n$(NC)"

#Debug
$(NAMEDB): $(LIBDB) $(OPATH) $(OBJD) $(OBJMD) $(INCS)
	$(CCD) $(DFLAGS) -o $@ $(LIBDB) $(OBJD) $(OBJMD)
	
$(OBJD) : $(OPATH)db%.o : %.c $(INCS)
	$(DEBUG) $(DFLAGS) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(BLUE)Compiling $< for debug\n$(NC)"

$(OBJMD) : $(OPATH)db%.o : %.c $(INCS)
	$(DEBUG) $(DFLAGS) $(CFLAGS) $(IFLAGS) $< -o $@
	printf "$(BLUE)Compiling $< for debug\n$(NC)"

#Libraries
$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

$(LIBDB) : FORCE
	$(MAKE) -C $(LPATH) debug

$(OPATH):
	$(MKDIR) $@

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYM)

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)

re: fclean all

FORCE :

.PHONY: all clean fclean debug test FORCE
.SILENT:
