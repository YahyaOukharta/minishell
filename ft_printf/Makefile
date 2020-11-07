NAME = libftprintf.a

LIBFTNAME = libft.a

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRCS = add_padding_char.c apply_precision_psign.c \
	add_padding_hex.c apply_precision_ptr.c p_dispatcher.c \
	add_padding_int.c apply_precision_s.c process.c \
	add_padding_percent_sign.c	apply_precision_uint.c process_utils.c \
	add_padding_ptr.c ft_printf.c t_convs_one.c \
	add_padding_string.c get_active_flag.c t_convs_two.c \
	add_padding_uint.c get_conv.c utils.c \
	apply_precision_c.c get_flags.c w_dispatcher.c \
	apply_precision_hex.c get_min_width.c apply_precision_int.c \
	get_precision.c

all: $(NAME)

$(LIBFTNAME):
	make -C libft/
	cp libft/$(LIBFTNAME) .

$(NAME): $(LIBFTNAME)
	ar -x libft.a
	gcc $(FLAGS) -c $(SRCS)
	ar -rc libftprintf.a *.o

clean:
	make -C libft/ clean
	rm -f *.o

fclean: clean
	make -C libft/ fclean
	rm -f $(LIBFTNAME)
	rm -f $(NAME)
	rm -f "__.SYMDEF SORTED"

re: fclean all
