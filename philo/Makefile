CFLAGS = -Wall -Wextra -Werror 
CFRAGS += -fsanitize=thread
CC = cc
SRCS = main.c routine.c time.c print.c init.c
NAME = philo
OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIB) -o $@

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re