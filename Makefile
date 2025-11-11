NAME    := push_swap
CC      := cc
FLAGS   := -Wall -Wextra -Werror -g
RM      := rm -f

SRCS    := push_swap.c parser.c list_operations.c stack_operations.c sort_operations.c
OBJS    := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cd libft ; make
	$(CC) $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@cd libft && make clean

fclean: clean
	$(RM) $(NAME)
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re