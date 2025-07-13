# -------- Makefile --------
# Flags e variáveis
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -static -s
SRCS    := main.c response.c request.c dtypes.c
OBJS    := $(SRCS:.c=.o)

# Alvo padrão
all: main response

# Binário principal
main: main.o
	$(CC) $(CFLAGS) -o $@ $^

response: response.o dtypes.o
	$(CC) $(CFLAGS) -o $@ $<

request: request.o
	$(CC) $(CFLAGS) -o $@ -c $@

request.o: request.c dtypes.c
	$(CC) $(CFLAGS) -o $@ $^

dtypes: dtypes.o
	$(CC) $(CFLAGS) -o $@ $<

# Regra genérica para .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Teste rápido
run: main
	./main

# Limpeza
clean:
	rm -f *.o main response

.PHONY: all run clean
# --------------------------
