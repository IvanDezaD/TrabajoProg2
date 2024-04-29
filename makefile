# Nombre del ejecutable final
TARGET = colocar.out

# Compilador
CC = g++

# Opciones de compilación
CFLAGS = -Wall -Wextra -std=c++11

# Carpetas de código fuente y de objetos
SRCDIR = src
OBJDIR = obj

# Archivos fuente
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Archivos objetos
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^

# Regla para construir los archivos objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
		$(CC) $(CFLAGS) -c $< -o $@

# Crear directorio de objetos si no existe
$(OBJDIR):
		mkdir -p $(OBJDIR)

# Regla para compilar en modo debug
debug:	CFLAGS += -D__DEBUG__
debug:	clean $(TARGET)

help:
	@echo "Uso: make [TARGET]"
	@echo " "
	@echo "Objetivos disponibles:"
	@echo "               Compila con modo release (sin mensajes extra de depuracion)"
	@echo "help      Mostrar este menú de ayuda"
	@echo "debug     Compila con modo de depuracion (incluye mensajes extra que ayudan a depurar como corre el programa)"
	@echo "clean     Limpia el binario y los .o generados durante la compilacion."
	@echo "          Por Ivan Deza y David Hudrea"

# Regla para limpiar
clean:
		rm -rf $(OBJDIR) $(TARGET)

# PHONY targets
.PHONY: clean debug help

