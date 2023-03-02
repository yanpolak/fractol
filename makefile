# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 13:37:24 by ymarival          #+#    #+#              #
#    Updated: 2023/03/02 19:35:44 by ymarival         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC						= main.c parse.c utils.c utils1.c mlx.c formulas.c draw.c complex.c ft_atol.c \

OBJ						= $(SRC:.c=.o)



NAME							= fractol

HDRS = mlx/

MLX = ./libmlx.dylib

CC								= gcc

CFLAGS							= -g -Wall -Wextra -Werror 

LIBS = -framework OpenGL -lm -framework AppKit

NB = $(words $(FILES)

%.o: %.c
	@$(CC) -g -I ${HDRS} -c $< -o $@


$(NAME): $(OBJ)
		
		@make -C ./mlx
		@mv mlx/libmlx.dylib .
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBS)
		@echo "$(C_LGRN)➜ [$(NAME)] Program has been Compiled Successfully !$(C_END)"	

RM								= rm -f


all:                    $(NAME)

clean:
	@${RM} $(OBJ)
	@echo "$(C_LMGN)➜ [$(NAME)] Objects have been cleaned Successfully !$(C_END)"




fclean:
	${RM} $(NAME) ${OBJ}
	@rm libmlx.dylib
	@make -C ./mlx clean
	@echo "$(C_LMGN)➜ [$(NAME)] Library has been deleted Successfully !$(C_END)"


re:							fclean $(NAME)

.PHONY:						all clean fclean re 