CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
OBJ = main.o jbk_shell

all: jbk_shell

jbk_shell: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o jbk_shell

clean:
	rm -f $(OBJ) jbk_shell