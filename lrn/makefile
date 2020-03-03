program = thread-safe

build: clean
	@ clear
	@ g++ main.cpp -o $(program) -pthread

run: build
	@ ./$(program)

clean:
	@ rm -f $(program)
