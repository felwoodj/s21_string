CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
OBJ_DIR = objects/
SOURCE = $(wildcard s21_*.c)
OBJECT = $(patsubst %.c, %.o, $(SOURCE))  # replace .c -> .o (making object files)
EXECUTABLE = test
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	GFLAGS = -lcheck_pic -lm -lsubunit
	RM_COMMAND = rm -rf test-s21_parse.gcda test-s21_parse.gcno test-s21_floats.gcda test-s21_floats.gcno test-s21_itoa.gcda test-s21_itoa.gcno test-test.gcda test-test.gcno
endif

ifeq ($(UNAME), Darwin)
	GFLAGS = -lcheck
	RM_COMMAND = rm test*.gcda test*.gcno s21_parse*.gcda s21_parse*.gcno s21_floats*.gcda s21_floats*.gcno s21_itoa*.gcda s21_itoa*.gcno
endif

all: clean s21_string.a

s21_string.a: clean $(OBJECT)
	# mkdir $(OBJ_DIR)
	ar rc s21_string.a $(OBJECT)
	ranlib s21_string.a
	rm -rf *.o

test: clean s21_string.a
	$(CC) $(CFLAGS) test.c s21_string.a -o $(EXECUTABLE) $(GFLAGS)
	./$(EXECUTABLE)

gcov_report: clean
	$(CC) $(CFLAGS) $(SOURCE) test.c -o $(EXECUTABLE) $(GFLAGS) --coverage
	./$(EXECUTABLE)
	lcov -t "tests" -o tests.info -c -d .
	genhtml -o report tests.info
	open report/index.html
	rm -rf *.gcno *.gcda *.gcov

style: clean
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format

clang: clean
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c
	clang-format -i *.h
	rm -rf .clang-format

clean:
	rm -f *.o *.a *.gcno *.gcda *.info $(EXECUTABLE)
	rm -rf report $(OBJ_DIR)
