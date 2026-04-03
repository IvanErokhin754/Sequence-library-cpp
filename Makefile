CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC = src/main.cpp src/UI.cpp
APP = app

TEST_SRC = tests/test_dynamic_array.cpp tests/test_linked_list.cpp 
TEST_BIN = tests_run
GTEST_FLAGS = $(shell pkg-config --cflags --libs gtest_main)

all: $(APP)

$(APP): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(APP)

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(GTEST_FLAGS) -o $(TEST_BIN)

run-tests: test
	./$(TEST_BIN)

clean:
	rm -f $(APP) $(TEST_BIN)

.PHONY: all test run-tests clean