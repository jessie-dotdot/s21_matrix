CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lcheck -lm -lpthread -lsubunit
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
REPORT_DIR = report

# Исходные файлы библиотеки
SRCS = $(wildcard $(SRC_DIR)/s21_*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Тестовые файлы (включая helpers)
TEST_SRCS = $(wildcard $(TEST_DIR)/s21_*_test.c) $(TEST_DIR)/test_helpers.c
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_SRCS))

TARGET = s21_matrix.a
TEST_EXEC = test

.PHONY: all clean test gcov_report

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(TARGET): $(OBJS)
	ar rcs $@ $^
	ranlib $@

test: CFLAGS += $(GCOV_FLAGS)
test: $(TARGET) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(TARGET) $(LIBS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: test
	lcov -t "$(TEST_EXEC)" -o $(BUILD_DIR)/$(TEST_EXEC).info -c -d .
	genhtml -o $(REPORT_DIR) $(BUILD_DIR)/$(TEST_EXEC).info
	open $(REPORT_DIR)/index.html

clean:
	rm -rf $(BUILD_DIR) $(REPORT_DIR) $(TARGET) $(TEST_EXEC) *.gcda *.gcno *.info