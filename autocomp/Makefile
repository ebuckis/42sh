# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/06 14:53:11 by kcabus       #+#   ##    ##    #+#        #
#    Updated: 2018/10/18 16:08:14 by kcabus      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libautocomp.a

WFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LIB_PATH = ../libft/


SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I $(INC_PATH) -I $(LIB_PATH)

OBJ_NAME = $(N_SRCS:.c=.o)

N_SRCS =	ac_init_slct.c			\
			ft_free_lst.c			\
			ac_init_slct2.c			\
			ac_lst_utils.c			\
			ac_lst_utils2.c			\
			ac_parse_line.c			\
			arrows.c				\
			arrows2.c				\
			autocomp.c				\
			display.c				\
			get_info.c				\
			key_func.c				\
			lib_ac.c				\
			change_tilde.c			\
			utils.c

all : $(NAME)

$(NAME):	$(OBJ)
			@ar rc $(NAME) $(OBJ) 
			@printf "\033[38;5;208m autocomp OK ! \n\033[0m"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@gcc -c $(WFLAGS) $(INC) -o $@ $<
				@printf "\033[48;5;208m \033[0m"
	
clean :
		@rm -rf $(OBJ_PATH)

fclean : 	clean
			@rm -rf $(NAME)

re : fclean clean all
