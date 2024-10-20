# Nombre del compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -Wall -Wextra -std=c++11 -lpthread

# Nombre del ejecutable
TARGET = CarreraDeBuses

# Archivo fuente
SRC = Carreradebuses.cpp

# Regla para compilar el ejecutable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)
