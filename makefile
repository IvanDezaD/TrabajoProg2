# Nombre del ejecutable final
TARGET = colocar.out

# Compilador
CC = g++

# Opciones de compilación
CFLAGS = -Wall -Wextra -std=c++11 -DMEMWATCH -DMW_STDIO

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

# Regla para limpiar
clean:
		rm -rf $(OBJDIR) $(TARGET)

# PHONY targets
.PHONY: clean debug

