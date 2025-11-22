NAME    := push_swap
CC      := cc
FLAGS   := -Wall -Wextra -Werror 
RM      := rm -f

SRCS    := push_swap.c parser/parser.c list_utils/list_operations.c operations/sa.c sort_utils/sort_operations.c sort_utils/sort_utils.c pushes/push_to_top.c find_utils/find_utils.c operations/reverse_rotate.c operations/rotate.c operations/push.c find_utils/find_costs.c pushes/from_a_to_b.c pushes/from_b_to_a.c target_utils/target_utils.c
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