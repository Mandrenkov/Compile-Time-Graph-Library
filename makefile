# Flags
# ------------------------------------------------------------------------------
# Allow users to specify their preferred C++ compiler.
COMPILER=g++
# Allow users to specify custom compiler flags.
FLAGS=-O2


# Paths
# ------------------------------------------------------------------------------
# Directories
BIN_DIR=./bin
CPP_DIR=./src/cpp
TEST_DIR=./src/test

# Executables
MAIN_EXE=$(BIN_DIR)/ctgl.exe
TEST_EXE=$(BIN_DIR)/ctgl_test.exe

# Files
TEST_FILES=$(wildcard $(TEST_DIR)/*_test.cpp)


# Rules
# ------------------------------------------------------------------------------
all: bin
	@rm -f $(MAIN_EXE)
	@$(COMPILER) $(FLAGS) -std=c++17 -Wfatal-errors -o $(MAIN_EXE) $(CPP_DIR)/ctgl.cpp
	@$(MAIN_EXE)

test: bin
	@rm -f $(TEST_EXE)
	@$(COMPILER) $(FLAGS) -std=c++17 -Wfatal-errors -o $(TEST_EXE) $(TEST_FILES) -lgtest -lgtest_main
	@$(TEST_EXE)

bin:
	@mkdir -p $(BIN_DIR)

clean:
	@rm -f $(BIN_DIR)