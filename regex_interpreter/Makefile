NAME		= regex
CC			= gcc
CC_FLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address

all:
	@make -C libft
	@$(CC) $(CC_FLAGS) main.c libft/libft.a -o $(NAME)

re:
	@make clean
	@make all

clean:
	@make fclean -C libft
	@rm -rf $(NAME)

fclean:
	@make clean
