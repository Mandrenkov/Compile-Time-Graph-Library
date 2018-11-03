all:
	@g++ -std=c++17 -Wfatal-errors -O2 -o ctgl.exe ctgl.cpp
	@./ctgl.exe

clean:
	@rm -f *.exe

