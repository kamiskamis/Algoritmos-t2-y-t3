# Nombre del ejecutable final
TARGET = programa

# Archivos fuente
SRCS = main.cpp fuerza_bruta.cpp p_dinamica.cpp

# Archivos de cabecera (para tenerlos listos en caso de que sea necesario)
HEADERS = fuerza_bruta.h p_dinamica.h

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Regla para compilar el ejecutable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Limpiar los archivos generados (ejecutable)
clean:
	rm -f $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
