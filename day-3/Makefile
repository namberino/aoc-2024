CC = $(shell which clang++)
CPP_FILE = solve.cpp
OUTPUT = solution
INPUT_FILE = input.txt

run: compile
	./$(OUTPUT) $(INPUT_FILE)

compile: solve.cpp
	$(CC) $(CPP_FILE) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
