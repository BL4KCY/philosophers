#______command and their flags______#
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread
CC = gcc
AR = ar -crs
INCLUDES = includes

#______directories______#
OBJ_DIR = obj
SRC_DIR = src
INCLUDES = includes

#______mandatory and bonus files______#
FILES = main.c
#______patterns and substitutions______#
SOURCES = $(FILES:%.c=$(SRC_DIR)/%.c)
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#______static library name______#
NAME = philo
#______________Rules______________#

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -I$(INCLUDES) -o $@

# impicit rule for mandatory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

re: fclean all

all: $(NAME)

#______cleaning______#
clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(BNS_DIR_OBJ)
fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
