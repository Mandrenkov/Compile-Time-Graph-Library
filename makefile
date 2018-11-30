# Allow users to specify their preferred C++ compiler from the command line. 
COMPILER=g++
FLAGS=

CPP_DIR="./src/cpp"
TEST_DIR="./src/test"

MAIN_EXE="ctgl.exe"
TEST_EXE="ctgl_test.exe"

all: bin
	@rm -f ./bin/$(MAIN_EXE)
	@$(COMPILER) $(FLAGS) -std=c++17 -Wfatal-errors -O2 -o bin/$(MAIN_EXE) $(CPP_DIR)/ctgl.cpp
	@./bin/$(MAIN_EXE)

test: bin
	@rm -f ./bin/$(TEST_EXE)
	@$(COMPILER) $(FLAGS) -std=c++17 -Wfatal-errors -O2 -o bin/$(TEST_EXE) $(TEST_DIR)/list_test.cpp $(TEST_DIR)/graph_test.cpp $(TEST_DIR)/algorithm_test.cpp -lgtest -lgtest_main
	@./bin/$(TEST_EXE)

bin:
	@mkdir -p ./bin

clean:
	@rm -f ./bin