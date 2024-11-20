# Variables
CC = g++              # El compilador C++
CFLAGS = -std=c++17 -Wall -g   # Flags para el compilador
LDFLAGS =              # Flags para el enlazador, si es necesario

# Archivos fuente
SRC = main.cpp fuerza_bruta.cpp p_dinamica.cpp
# Archivos objeto generados
OBJ = $(SRC:.cpp=.o)
# Nombre del archivo ejecutable
EXEC = programa

# Regla para compilar y enlazar el ejecutable
all: $(EXEC)

# Regla para generar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Regla para compilar sin generar archivos nuevos (solo objetos)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para ejecutar el programa
run: $(EXEC)
	./$(EXEC)

# Regla para limpiar (eliminar archivos generados)
clean:
	rm -f *.o $(EXEC)
