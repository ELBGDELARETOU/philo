NAME = philo

SRCS = new_test.c input_check.c utils.c

OBJS = ${SRCS:.c=.o}

CC = cc -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${SRCS} makefile philo.h 
		${CC} ${SRCS} -g3 -o ${NAME}

clean:
		rm -rf ${OBJS}
		rm -f ./libft.a
		make -C ./libft clean

fclean:
		rm -rf ${NAME} ${OBJS}
		rm -f ./libft.a
		rm -f ./libmlx.a
		make -C ./libft fclean
		make -C ./minilibx-linux clean

re: fclean all