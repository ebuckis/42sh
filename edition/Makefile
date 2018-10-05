# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/06 14:53:11 by kcabus       #+#   ##    ##    #+#        #
#    Updated: 2018/09/14 13:36:49 by kcabus      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libedition.a

WFLAGS = -Wall -Wextra -Werror

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LIB_PATH = ../libft/


SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I $(INC_PATH) -I $(LIB_PATH)

OBJ_NAME = $(N_SRCS:.c=.o)

N_SRCS =	ft_edition.c			\
			ft_putcharint.c			\
			ft_get_size.c			\
			ft_init_nav.c			\
			ft_key_move.c			\
			ft_recup_pos.c			\
			ft_x_change.c			\
			ft_default_edit.c		\
			ft_del_char.c			\
			ft_new_char.c			\
			ft_move_to_xy.c			\
			ft_key_code.c			\
			ft_push_enter.c			\
			ft_verif_term_size.c	\
			ft_move_up.c			\
			ft_key_alt.c			\
			ft_maj_line.c			\
			ft_maj_win.c			\
			ft_give_hist.c			\
			ft_historique.c			\
			ft_close_hist.c			\
			ft_copy_paste.c			\
			ft_gestion_signal.c		\
			ft_init_term.c			\
			ft_del_end_to_i.c		\
			ft_ring_the_bell.c		\
			ft_delta_line.c			\
			ft_goto_i_from_end.c

all : $(NAME)

$(NAME):	$(OBJ)
			@ar rc $(NAME) $(OBJ)
			@printf "\033[33m edition OK ! \n\033[0m"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@gcc -c $(WFLAGS) $(INC) -o $@ $<
				@printf "\033[43m \033[0m"
	
clean :
		@rm -rf $(OBJ_PATH)

fclean : 	clean
			@rm -rf $(NAME)

re : fclean clean all
