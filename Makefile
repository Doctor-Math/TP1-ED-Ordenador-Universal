# Diretórios
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INC_DIR := include

# Arquivos
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXEC := $(BIN_DIR)/tp1.out

# Compilador e flags
CXX := g++
CXXFLAGS := -Wall -Wextra -I$(INC_DIR) -std=c++17

# Regra principal
all: $(EXEC)

# Compilação do executável
$(EXEC): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@chmod +x $@

# Compilação dos .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

.PHONY: all clean