all:
	@g++ -std=c++17 -Wfatal-errors -O2 -o ctgl.exe ctgl.cpp
	@./ctgl.exe

test:
	@g++ -std=c++17 -Wfatal-errors -O2 -o ctgl_test.exe list_test.cpp graph_test.cpp -lgtest -lgtest_main
	@./ctgl_test.exe

clean:
	@rm -f *.exe

