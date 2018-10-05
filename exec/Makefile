# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/06 14:53:11 by kcabus       #+#   ##    ##    #+#        #
#    Updated: 2018/09/14 11:58:11 by kcabus      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libexec.a

WFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LIB_PATH = ../libft/


SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I $(INC_PATH) -I $(LIB_PATH)

OBJ_NAME = $(N_SRCS:.c=.o)

N_SRCS =	cd.c					\
			check_bin.c				\
			check_builtin.c			\
			echo.c					\
			env.c					\
			execve.c				\
			fg.c					\
			fork.c					\
			ft_redir_in.c			\
			ft_redir_out.c			\
			getenv.c				\
			manage_redir.c			\
			manage_signal.c			\
			pipes.c					\
			redir.c					\
			ret_display.c			\
			setenv.c				\
			unsetenv.c

all : $(NAME)

$(NAME):	$(OBJ)
			@ar rc $(NAME) $(OBJ) 
			@printf "\033[35m exec OK ! \n\033[0m"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@gcc -c $(WFLAGS) $(INC) -o $@ $<
				@printf "\033[45m \033[0m"
	
clean :
		@rm -rf $(OBJ_PATH)

fclean : 	clean
			@rm -rf $(NAME)

re : fclean clean all
