NAME = minishell

SRCS = main.c

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c

GNL_BUFFER_SIZE = -D BUFFER_SIZE=100

FT_PRINTF_PATH = ft_printf/

FLAGS = -fsanitize=address -g #-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C $(FT_PRINTF_PATH)
	gcc $(FLAGS) $(SRCS) $(GNL_SRCS) $(GNL_BUFFER_SIZE) -L$(FT_PRINTF_PATH) -lftprintf  -o $(NAME)

clean:
	make -C $(FT_PRINTF_PATH) clean
	rm -rf *.o

fclean: clean
	make -C $(FT_PRINTF_PATH) fclean
	rm -rf $(NAME)

re: fclean all

c: re
	./$(NAME)