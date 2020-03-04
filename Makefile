# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 09:25:56 by jcorral-          #+#    #+#              #
#    Updated: 2020/03/03 13:09:35 by jcorral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c ./get_next_line/get_next_line.c parse_cub.c parse_cub_utils.c parse_cub_utils3.c  wall_raycasting.c wall_raycasting_utils.c sprite_raycasting.c sprite_count.c movement.c key_events.c game_init.c game_init2.c valid_map.c valid_map2.c game_close.c bmp.c

OBJS		= ${SRCS:.c=.o}

NAME		= cub3d

CC			= cc

RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra

framework	= -L . -lmlx -lft -framework OpenGL -framework AppKit

.c.o:
			${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${MAKE} -C ./minilibx
			${MAKE} -C ./libft
			mv ./minilibx/libmlx.a .
			mv ./libft/libft.a .
			${CC} -o ${NAME} ${OBJS} ${framework}
			

all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./minilibx
			${MAKE} clean -C ./libft

fclean : 	clean
			${RM} ${NAME} libmlx.a libft.a

re:			fclean all

.PHONY:		re all clean fclean
