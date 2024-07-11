NAME = philo
BONUS_NAME = philo_bonus

SRCS = \
			main.c \
			table.c \
			check.c \
			clean.c \
			errors.c \
			philos.c \
			print.c \
			monitor.c \
			threads.c \
			threads_philo.c \
			forks.c \
			ft_atoi.c \
			ft_calloc.c \
			locks.c \

SRCS_DIR = sources
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = objects

BONUS_SRCS = \
			main_bonus.c \
			table_bonus.c \
			check_bonus.c \
			clean_bonus.c \
			errors_bonus.c \
			philos_bonus.c \
			print_bonus.c \
			monitor_bonus.c \
			threads_bonus.c \
			threads_philo_bonus.c \
			forks_bonus.c \
			ft_atoi_bonus.c \
			ft_calloc_bonus.c \
			locks_bonus.c \

BONUS_SRCS_DIR = sources/bonus
BONUS_OBJS = $(BONUS_SRCS:%.c=$(BONUS_OBJS_DIR)/%.o)
BONUS_OBJS_DIR = objects/bonus

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Wunreachable-code -Ofast
CFLAGS += -g -pthread
CFLAGS += -g
#CFLAGS += -g -pthread -fsanitize=thread 
#CFLAGS += -g -pthread -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@echo "Compilation in Progress"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "********Completed********"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS_DIR) $(BONUS_OBJS)
	@echo " ***BONUS*** Compilation in Progress"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "********Completed********"

$(BONUS_OBJS_DIR):
	@mkdir -p $(BONUS_OBJS_DIR)

$(BONUS_OBJS_DIR)/%.o:$(BONUS_SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@echo "Cleaning in Progress"
	@rm -rf $(OBJS_DIR)
	@rm -rf $(BONUS_OBJS_DIR)
	@echo "Cleaning Completed"

fclean:
	@echo "Cleaning in Progress"
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -f ./a.out
	@rm -f ./sources/a.out
	@rm -f ./sources/bonus/a.out
	@rm -f ./philo
	@rm -f ./philo_bonus
	@rm -rf $(BONUS_OBJS_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "***Cleaning Completed***"
	@echo ""

re: fclean all

.PHONY: all bonus clean fclean re
