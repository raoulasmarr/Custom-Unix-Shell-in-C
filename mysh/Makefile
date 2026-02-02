CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g
TARGET = mysh
LDFLAGS = 
SRCS = src/main.c src/parser.c src/executer.c src/builtins.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all


