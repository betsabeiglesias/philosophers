NAME = philo

SRC_DIR = ./src
OBJ_DIR = ./obj
INC = ./inc

CC = cc
NO_LINK = -c
CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -lpthread

SRC = main.c \
		checkings.c \
		aux.c \
		dinner.c monitor.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(NO_LINK) $(CFLAGS) -I$(INC) $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) 

clean:
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi

re: fclean all

.PHONY: all fclean clean re lib sanitizer

#.SILENT: