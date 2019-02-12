# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 23:18:40 by cempassi          #+#    #+#              #
#    Updated: 2019/02/11 23:49:12 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libftdb.a

CC = Clang
COMPILE = $(CC) -c
DEBUG = $(CC) -g

MKDIR = mkdir -p
CLEANUP = rm -rf

WFLAGS += -Wall
WFLAGS += -Werror
WFLAGS += -Wextra
DFLAGS = -fsanitize=address
IFLAGS = -I $(IPATH) -I $(LIPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)

OPATH = obj/
SPATH = srcs/
IPATH = includes/
LPATH = libft/
LIPATH = libft/includes/

SRCS += main.c
SRCS += env.c
SRCS += builtin.c
INCS += minishell.h
DSYM = $(NAME).dSYM

OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))

vpath %.c srcs
vpath %.h includes

all : $(LIB) $(NAME)

run : $(LIB) $(NAME)
	./$(NAME)

debug : $(LIBDB) $(SRCS)
	$(DEBUG) $(DFLAGS) $(CFLAGS) -o $(NAME) $^

$(NAME): $(LIB) $(OPATH) $(OBJS) $(INCS)
	$(CC) -o $@ $(LIB) $(OBJS)

$(OBJS) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

$(LIBDB) :
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

re: fclean all

FORCE :

.PHONY: all clean fclean debug FORCE
