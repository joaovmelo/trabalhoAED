# Executável final
TARGET = trem

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g

# Arquivos-fonte
SRCS = main.c Interface.c Trem.c Vagao.c

# Arquivos-objeto correspondentes
OBJS = $(SRCS:.c=.o)

# Alvo padrão
all: $(TARGET)

# Como gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar binários e objetos
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
