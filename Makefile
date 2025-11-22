NAME    := push_swap
CC      := cc
FLAGS   := -Wall -Wextra -Werror -g
RM      := rm -f

SRCS    := push_swap.c parser/parser.c list_operations.c operations/sa.c sort_operations.c sort_utils.c turk_utils.c find_utils/find_utils.c operations/reverse_rotate.c operations/rotate.c operations/push.c find_utils/find_costs.c pushes/from_a_to_b.c pushes/from_b_to_a.c
OBJS    := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cd libft && make
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