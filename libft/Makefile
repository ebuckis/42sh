# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 08:13:59 by kcabus       #+#   ##    ##    #+#        #
#    Updated: 2018/09/14 11:58:25 by kcabus      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a

WFLAGS = -Wall -Wextra -Werror

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/

SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I $(INC_PATH)

OBJ_NAME = $(N_SRCS:.c=.o)

N_SRCS =	ft_memset.c					\
			ft_bzero.c					\
			ft_memcpy.c					\
			ft_memcpy.c					\
			ft_memcpy.c					\
			ft_memcpy.c					\
			ft_memcpy.c					\
			ft_memcpy.c					\
			ft_memcpy.c					\
			ft_memcpy.c					\
			ft_memccpy.c				\
			ft_memmove.c				\
			ft_memchr.c					\
			ft_memcmp.c					\
			ft_strlen.c					\
			ft_strdup.c					\
			ft_strdup_wchar.c			\
			ft_strcpy.c					\
			ft_strncpy.c				\
			ft_strcat.c					\
			ft_strncat.c				\
			ft_strlcat.c				\
			ft_strchr.c					\
			ft_strrchr.c				\
			ft_strstr.c					\
			ft_strnstr.c				\
			ft_strcmp.c					\
			ft_strncmp.c				\
			ft_atoi.c					\
			ft_isalpha.c				\
			ft_isdigit.c				\
			ft_isalnum.c				\
			ft_isascii.c				\
			ft_isprint.c				\
			ft_toupper.c				\
			ft_tolower.c				\
			ft_memalloc.c				\
			ft_memdel.c					\
			ft_strnew.c					\
			ft_strdel.c					\
			ft_strclr.c					\
			ft_striter.c				\
			ft_striteri.c				\
			ft_strmap.c					\
			ft_strmapi.c				\
			ft_strequ.c					\
			ft_strnequ.c				\
			ft_strsub.c					\
			ft_strjoin.c				\
			ft_strtrim.c				\
			ft_strsplit.c				\
			ft_itoa.c					\
			ft_putchar.c				\
			ft_putstr.c					\
			ft_putendl.c				\
			ft_putnbr.c					\
			ft_putchar_fd.c				\
			ft_putstr_fd.c				\
			ft_putendl_fd.c				\
			ft_putnbr_fd.c				\
			ft_lstnew.c					\
			ft_lstdel.c					\
			ft_lstdelone.c				\
			ft_lstadd.c					\
			ft_lstiter.c				\
			ft_lstmap.c					\
			ft_swap.c					\
			ft_strrev.c					\
			ft_pw.c						\
			ft_sqrt.c					\
			cpt_mot.c					\
			get_next_line.c				\
			ft_isprime.c				\
			ft_strsub_del.c				\
			ft_whitespace.c				\
			ft_strjoin_del.c			\
			ft_realloc.c				\
			ft_printf.c					\
			ft_printf_type.c			\
			ft_printf_c.c				\
			ft_printf_d1.c 				\
			ft_printf_d2.c				\
			ft_printf_e.c				\
			ft_printf_f.c				\
			ft_printf_g.c				\
			ft_printf_n1.c				\
			ft_printf_n2.c				\
			ft_printf_o1.c				\
			ft_printf_o2.c				\
			ft_printf_p.c				\
			ft_printf_s.c				\
			ft_printf_percent.c			\
			ft_printf_u1.c				\
			ft_printf_u2.c				\
			ft_printf_x1.c				\
			ft_printf_x2.c				\
			ft_putwchar.c				\
			ft_putstr_size.c			\
			ft_putchar_size.c			\
			ft_putwstr.c				\
			ft_wstrlen.c				\
			ft_putnbr_size.c			\
			ft_putnbr_double.c			\
			ft_nbr_size.c				\
			ft_nbr_size_base.c			\
			ft_putnbr_base.c			\
			parse.c						\
			parse2.c					\
			parse3.c ft_two_pow.c		\
			ft_two_pow2.c			 	\
			ft_sum.c ft_sum2.c			\
			ft_round.c					\
			ft_putnbr_longdouble.c 		\
			ft_putnbr_double_sci.c		\
			ft_putnbr_double_sci2.c		\
			ft_putnbr_longdouble_sci.c	\
			ft_putnbr_double_denormalized.c

all : $(NAME)

$(NAME) :	$(OBJ)
			@ar rc $(NAME) $(OBJ)
			@printf "\033[32m libft OK ! \n\033[0m"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@gcc -c $(WFLAGS) $(INC) -o $@ $<
				@printf "\033[42m \033[0m"
	
clean :
			@rm -rf $(OBJ_PATH)

fclean : 	clean
			@rm -rf $(NAME)

re : fclean clean all
