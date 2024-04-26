# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC = src/jv.c
EXEC = jv

# Alvo padrão
all: $(EXEC)

# Compilação
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# Limpeza
clean:
	rm -f $(EXEC)
