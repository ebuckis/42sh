# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/06 14:53:11 by kcabus       #+#   ##    ##    #+#        #
#    Updated: 2018/12/04 10:47:29 by yoginet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re compile

NAME = 42sh

WFLAGS = -Wall -Wextra -Werror

SRC_PATH	=	./
INC_PATH	=	./includes/
OBJ_PATH	=	./obj/
LIB_PATH	=	./libft/
EDIT_PATH	=	./edition/
PARSE_PATH	=	./parser/
AUTOCOMP_PATH = ./autocomp/
EXEC_PATH	=	./exec/


SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC =		-I $(LIB_PATH)		\
			-I $(EDIT_PATH)		\
			-I $(PARSE_PATH)	\
			-I $(AUTOCOMP_PATH)	\
			-I $(EXEC_PATH)

OBJ_NAME = $(N_SRCS:.c=.o)

N_SRCS =	main.c

LIB_A =		-L $(LIB_PATH) -lft				\
			-L $(PARSE_PATH) -lparser		\
			-L $(EDIT_PATH) -ledition		\
			-L $(EXEC_PATH) -lexec			\
			-L $(AUTOCOMP_PATH) -lautocomp	\
			-ltermcap

all : $(NAME)

$(NAME):	$(OBJ) compile
			@gcc $(WFLAGS) $(OBJ) $(INC) $(LIB_A) -o $(NAME)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c 
			@mkdir -p $(OBJ_PATH)
			@gcc -c $(WFLAGS) $(INC) -o $@ $<
	
compile :
			@make -C $(LIB_PATH)
			@make -C $(PARSE_PATH)
			@make -C $(EDIT_PATH)
			@make -C $(EXEC_PATH)
			@make -C $(AUTOCOMP_PATH)

clean :
			@make -C $(LIB_PATH) clean
			@make -C $(PARSE_PATH) clean
			@make -C $(EDIT_PATH) clean
			@make -C $(EXEC_PATH) clean
			@make -C $(AUTOCOMP_PATH) clean
			@rm -rf $(OBJ_PATH)

fclean : 	clean
			@make -C $(LIB_PATH) fclean
			@make -C $(PARSE_PATH) fclean
			@make -C $(EDIT_PATH) fclean
			@make -C $(EXEC_PATH) fclean
			@make -C $(AUTOCOMP_PATH) fclean
			@rm -rf $(NAME)

re : fclean clean all
