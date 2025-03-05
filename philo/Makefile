CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude -g 
# CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude -g -fsanitize=thread
SRC = 	main.c \
		input_parsing.c \
		utils.c \
		init.c \
		routine.c \
		start.c \
		time_utils.c \
		eat.c \
		monitor.c \
		free.c \
		sleep.c \
		
SRCS = $(addprefix src/, $(SRC))
OBJSDIR = obj
OBJS = $(addprefix $(OBJSDIR)/, $(notdir $(SRCS:.c=.o)))

NAME = philo

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJSDIR)/%.o: src/%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean clean all re bonus
