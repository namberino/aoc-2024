CC = $(shell which clang++)
C_FLAGs = -std=c++17
CPP_FILE = solve.cpp
OUTPUT = solution
INPUT_FILE = input.txt
TEST_FILE = test.txt

run: compile
	./$(OUTPUT) $(INPUT_FILE)

test: compile
	./$(OUTPUT) $(TEST_FILE)

compile: $(CPP_FILE)
	$(CC) $(C_FLAGs) $(CPP_FILE) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
