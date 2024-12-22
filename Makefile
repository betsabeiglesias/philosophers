NAME = philo

SRCS = main.c \
		checkings.c \
		aux.c \
		dinner.c monitor.c

OBJ_DIR = ./obj

CC = cc
NO_LINK = -c
CFLAGS = -Wall -Werror -Wextra
INC = -I./philosophers.h
LDFLAGS = -lpthread

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
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