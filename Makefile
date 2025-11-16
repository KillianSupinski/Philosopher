# Program name
NAME        = philo

# Directories
SRCDIR      = srcs
INCDIR      = includes
OBJDIR      = objs

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
DEPFLAGS    = -MMD -MP
LDFLAGS     = -pthread

# Include paths
INCLUDES    = -I$(INCDIR)

# Source files (tous les .c dans srcs/ et sous-dossiers)
SOURCES 	=	$(SRCDIR)/main.c \
        		$(SRCDIR)/utils.c \
		  		$(SRCDIR)/init.c \
		  		$(SRCDIR)/routine.c \
		  		$(SRCDIR)/monitoring.c \
				$(SRCDIR)/utils2.c		

# Object files and dependencies
OBJS        = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS        = $(OBJS:.o=.d)

# Colors for output
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
PURPLE      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m
RESET       = \033[0m

# ASCII Art (optionnel)
PHILO_ART   = $(BLUE)""$(RESET)

# Main target
all: $(NAME)

# Compile objects (crée automatiquement les sous-dossiers de objs/)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling $(CYAN)%-40s$(YELLOW) -> $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

# Link program
$(NAME): $(OBJS)
	@printf "$(PURPLE)Linking $(CYAN)$(NAME)$(PURPLE)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(PHILO_ART)"
	@printf "$(GREEN)✅ $(WHITE)$(NAME) $(GREEN)compilé avec succès !$(RESET)\n\n"

# Clean object files
clean:
	@printf "$(RED)Nettoyage des objets...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)✅ Objets nettoyés !$(RESET)\n"

# Full clean
fclean: clean
	@printf "$(RED)Suppression de $(CYAN)$(NAME)$(RED)...$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)✅ Nettoyage complet effectué !$(RESET)\n"

# Rebuild
re: fclean all
	@printf "$(CYAN)🔄 Rebuild terminé !$(RESET)\n"

# Debug targets
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: re
	@printf "$(YELLOW) Version debug construite avec AddressSanitizer$(RESET)\n"

tsan: CFLAGS += -DDEBUG -fsanitize=thread
tsan: re
	@printf "$(YELLOW) Version debug construite avec ThreadSanitizer$(RESET)\n"

# Run target
run: all
	@printf "$(GREEN)Lancement de $(CYAN)$(NAME)$(GREEN)...$(RESET)\n"
	@./$(NAME)

# Include dependencies
-include $(DEPS)

.PHONY: all clean fclean re debug tsan run