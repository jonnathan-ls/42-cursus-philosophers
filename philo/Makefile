# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 12:02:46 by jlacerda          #+#    #+#              #
#    Updated: 2025/05/24 21:01:03 by jlacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
OBJS_DIR = ./objects
INCS_DIR = ./includes

SRCS = sources/commons.c sources/utils.c sources/exit.c \
	sources/handlers.c sources/main.c 

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread -I$(INCS_DIR)

RESET = \033[0m
BOLD = \033[1m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

TOTAL_FILES := $(words $(SRCS))
BAR_LENGTH = $(TOTAL_FILES)
COMPILED_COUNT = 0

all: header $(NAME)

header:
	@if [ ! -f .header_lock ]; then \
		touch .header_lock; \
		echo; \
		echo "$(MAGENTA)$(BOLD)🔥  P H I L O S O P H E R S$(RESET)"; \
		echo "$(GREEN)$(BOLD)👥  Autor:$(RESET) $(YELLOW)jonnathan-ls$(RESET)"; \
		echo; \
	fi

$(NAME): $(OBJS)
	@printf "\n$(BLUE)$(BOLD)🔗  Linkando arquivos ...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(BOLD)🚀 Philosophers compilado com sucesso!$(RESET)"
	@echo
	@rm -f .header_lock

$(OBJS_DIR)/%.o: %.c 
	@mkdir -p $(dir $@)
	@$(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT)+1))))
	@$(eval SHORT_PATH=$(shell echo $< | sed 's|sources/||'))
	@$(CC) $(CFLAGS) -c $< -o $@
	@if [ $(COMPILED_COUNT) -eq 1 ]; then \
		echo ""; \
		printf "$(BLUE)$(BOLD)🏗️   Compilando Philosophers $(RESET)\n"; \
	fi
	@if [ $(COMPILED_COUNT) -gt 1 ]; then \
		printf "\033[2A\r"; \
	fi

	@printf "$(CYAN)$(BOLD)📄  Processando $(RESET)($(COMPILED_COUNT)/$(TOTAL_FILES)) \
	$(CYAN)$(SHORT_PATH)$(RESET)%*s\r\n" $$(( 60 - $${#SHORT_PATH} )) " "
	@$(eval FILLED=$(shell echo $$(($(COMPILED_COUNT)*$(BAR_LENGTH)/$(TOTAL_FILES)))))
	@printf "$(YELLOW)$(BOLD)🔄  $(RESET)$(YELLOW)%s$(RESET) \n" "$(shell printf '▓%.0s' $$(seq 1 $(FILLED)))"

	@if [ $(COMPILED_COUNT) -eq $(TOTAL_FILES) ]; then \
		sleep 0.3; \
		printf "\033[3A\r"; \
		printf "                                                              \r"; \
		printf "$(BLUE)$(BOLD)🏗️   Compilando o programa $(GREEN)$(BOLD)✓ Concluído!$(RESET)\n"; \
		printf "$(CYAN)$(BOLD)📄  Processando $(RESET)($(COMPILED_COUNT)/$(TOTAL_FILES)) \
		$(CYAN)$(SHORT_PATH)$(RESET)%*s\n" $$(( 60 - $${#SHORT_PATH} )) " "; \
		printf "$(YELLOW)$(BOLD)🔄  $(RESET)$(YELLOW)%s$(RESET) \n" "$(shell printf '▓%.0s' $$(seq 1 $(FILLED)))"; \
	fi

clean: header
	@printf "$(MAGENTA)$(BOLD)🗑️   Limpando arquivos objeto $(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)$(BOLD)✓ Objetos removidos!$(RESET)"
	@rm -f .header_lock

fclean: header
	@printf "$(MAGENTA)$(BOLD)🗑️   Limpando arquivos objeto $(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)$(BOLD)✓ Concluído!$(RESET)"
	@printf "$(MAGENTA)$(BOLD)🗑️   Limpando executável $(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(BOLD)✓ Concluído!$(RESET)"
	@rm -f .header_lock
	@echo

re:
	@rm -f .header_lock
	@$(MAKE) --no-print-directory -s fclean all

valgrind: fclean 
	@rm	-f .header_lock
	@make CFLAGS="-Wall -Wextra -Werror -g -I$(INCS_DIR)" --no-print-directory -s

helgrind: valgrind
	@echo "$(BLUE)$(BOLD)🔍 Analisando race conditions com Helgrind ...$(RESET)"
	@valgrind -s \
	--track-fds=yes \
	--tool=helgrind \
	./$(NAME) $(ARGS)

memcheck: valgrind
	@echo "$(BLUE)$(BOLD)🔍 Analisando vazamentos de memória com Memcheck ...$(RESET)"
	@valgrind -s \
	--tool=memcheck \
	--leak-check=full \
	--track-origins=yes \
	--show-reachable=yes \
	--show-leak-kinds=all \
	./$(NAME) $(ARGS)

.PHONY: all clean fclean re header