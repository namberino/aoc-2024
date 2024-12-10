CC = $(shell which clang++)
CPP_FILE = solve.cpp
OUTPUT = solution
INPUT_FILE = input.txt
TEST_FILE = test.txt

run: compile
	./$(OUTPUT) $(INPUT_FILE)

test: compile
	./$(OUTPUT) $(TEST_FILE)

compile: solve.cpp
	$(CC) $(CPP_FILE) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
