# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/06 14:53:11 by kcabus       #+#   ##    ##    #+#        #
#    Updated: 2018/09/14 11:57:56 by kcabus      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libparser.a

WFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LIB_PATH = ../libft/


SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I $(INC_PATH) -I $(LIB_PATH)

OBJ_NAME = $(N_SRCS:.c=.o)

N_SRCS =	ft_parser.c				\
			ft_antislash.c			\
			ft_init_parse.c			\
			ft_separator.c			\
			ft_is_separator.c		\
			ft_is_white.c			\
			ft_parse_dquote.c		\
			ft_parse_quote.c		\
			ft_suite_line.c			\
			ft_save_struct.c		\
			ft_close_parse.c		\
			ft_heredoc.c			\
			ft_tilde_dollar.c		\
			ft_dollar.c

all : $(NAME)

$(NAME):	$(OBJ)
			@ar rc $(NAME) $(OBJ) 
			@printf "\033[34m parser OK ! \n\033[0m"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@gcc -c $(WFLAGS) $(INC) -o $@ $<
				@printf "\033[44m \033[0m"
	
clean :
			@rm -rf $(OBJ_PATH)

fclean : 	clean
			@rm -rf $(NAME)

re : fclean clean all
