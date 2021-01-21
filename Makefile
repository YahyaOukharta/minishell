NAME = minishell

GNL_PATH = gnl

GNL_SRCS = $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c

GNL_BUFFER_SIZE = -D BUFFER_SIZE=100

FT_PRINTF_PATH = ft_printf/

INCLUDES = includes/

SRCS = srcs/main.c\
		\
	   srcs/environment/env1.c\
	   srcs/environment/env2.c\
	   srcs/environment/env3.c\
		\
	   srcs/builtins/builtins1.c\
	   srcs/builtins/builtins2.c\
	   srcs/builtins/builtins_utils.c\
		\
	   srcs/parser/check_syntax.c\
	   srcs/parser/check_line.c\
	   srcs/parser/parser_env.c\
	   srcs/parser/demo_parser.c\
	   srcs/parser/parser_redir.c\
	   srcs/parser/parser.c\
	   srcs/parser/free_parsed.c\
	   srcs/parser/check_line_utils.c\
	   srcs/parser/norm_utils.c\
	   srcs/parser/syntax_norm.c\
	   srcs/parser/syntax_norm_utils.c\
	   srcs/parser/check_line_nu.c\
	   srcs/parser/get_arg.c\
	   srcs/parser/get_tokens.c\
	   srcs/parser/append_helper.c\
		\
	   srcs/execution/processes.c\
	   srcs/execution/processes_utils.c\
	   srcs/execution/perm_utils.c\
	   srcs/execution/path.c\
	   srcs/execution/redirections.c\
	   srcs/execution/pipelines.c\
		\
	   srcs/signals/signals.c\
		\
	   srcs/utils/main_utils.c\
	   srcs/utils/tab_utils.c\
	   srcs/utils/utils.c\

FLAGS = -g -o3 -Wall -Wextra -Werror #-fsanitize=address 

GCC = gcc

all: $(NAME)

$(NAME):
	make -C $(FT_PRINTF_PATH)
	$(GCC) $(FLAGS) $(SRCS) $(GNL_SRCS) $(GNL_BUFFER_SIZE) \
		-L $(FT_PRINTF_PATH) -lftprintf \
		-I $(INCLUDES) -I $(FT_PRINTF_PATH) -I $(GNL_PATH) \
		-o $(NAME)
	# remove \^
	#stty -ctlecho
clean:
	make -C $(FT_PRINTF_PATH) clean
	rm -rf *.o

fclean: clean
	make -C $(FT_PRINTF_PATH) fclean
	rm -rf $(NAME)
	rm -rf minishell.dSYM

re: fclean all

c: re
	./$(NAME)

n:
	norminette $(SRCS) $(INCLUDES)