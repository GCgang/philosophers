CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SOURCES = main.c \
		 philo_utils.c \
		 initialize.c \
		 finalize.c \
		 routine.c \
		 monitor.c \
		 time.c

OBJS = $(SOURCES:.c=.o)
OBJECTS = $(OBJS)

all: $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
clean :
	rm -rf $(OBJS) $(B_OBJS)

fclean : clean
	rm -rf $(NAME)
re :
	make fclean
	make all

.PHONY : all clean fclean re