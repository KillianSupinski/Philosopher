NAME    = philo
SRC_DIR = srcs
SRCS    = $(SRC_DIR)/main.c \
          $(SRC_DIR)/utils.c \
		  $(SRC_DIR)/init.c
OBJS    = $(SRCS:.c=.o)
DEPS    = $(SRCS:.c=.d)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -MMD -MP

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Compilation terminée : $(NAME)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(DEPS)
	@echo "Objets et dépendances supprimés."

fclean: clean
	@rm -f $(NAME)
	@echo "Binaire supprimé."

re: fclean all

.PHONY: all clean fclean re