CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = main.c\
		input_parsing.c\
		utils.c\

SRCS = $(addprefix src/, $(SRC))
OBJSDIR = obj
OBJS = $(addprefix $(OBJSDIR)/, $(notdir $(SRCS:.c=.o)))

BONUS_SRC = 

BONUS_SRCS = $(addprefix src/bonus/, $(BONUS_SRC))
BONUS_OBJSDIR = obj_bonus
BONUS_OBJS = $(addprefix $(BONUS_OBJSDIR)/, $(notdir $(BONUS_SRCS:.c=.o)))

NAME = philo
BONUS_NAME = philo_bonus

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJSDIR)/%.o: src/%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS)

$(BONUS_OBJSDIR)/%.o: src/%.c | $(BONUS_OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJSDIR):
	mkdir -p $(BONUS_OBJSDIR)

clean:
	rm -rf $(OBJSDIR)

clean_bonus :
	rm -rf $(BONUS_OBJSDIR)

fclean: clean
	rm -rf $(NAME)

fclean_bonus: clean clean_bonus
	rm -rf $(BONUS_NAME)
re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: fclean clean all re bonus fclean_bonus clean_bonus re_bonus
