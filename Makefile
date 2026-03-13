CC = gcc
CFLAGS = -Wall -Wextra -O2
EXE = storage

.PHONY: all build run clean rebuild test

all: build run
build:
	$(CC) $(CFLAGS) `ls *.c | grep -v test.c` -o $(EXE)
run:
	./$(EXE)
clean:
	rm -f $(EXE) test_runner *.gcda *.gcno coverage.info 
	rm -rf out
rebuild: clean all

test:
	$(CC) $(CFLAGS) --coverage `ls *.c | grep -v main.c` -o test_runner
	./test_runner

coverage: test
coverage: test
	lcov --capture --directory . --output-file coverage.info --rc branch_coverage=1
	lcov --remove coverage.info '$(PWD)/test*' --output-file coverage.info --rc branch_coverage=1
	genhtml coverage.info --output-directory out --rc branch_coverage=1
