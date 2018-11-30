# Allow users to specify their preferred C++ compiler from the command line. 
COMPILER=g++
FLAGS=

all:
	@$(COMPILER) $(FLAGS) -std=c++17 -Wfatal-errors -O2 -o ctgl.exe ctgl.cpp
	@./ctgl.exe

test:
	@$(COMPILER) $(FLAGS) -std=c++17 -Wfatal-errors -O2 -o ctgl_test.exe list_test.cpp graph_test.cpp algorithm_test.cpp -lgtest -lgtest_main
	@./ctgl_test.exe

clean:
	@rm -f *.exe

