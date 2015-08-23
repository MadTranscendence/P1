TARGET   = $(BIN_DIR)/P1.elf

CXX     ?= g++

CXXFLAGS = $(INCLUDES) -std=c++11 -Wall -Wextra -Wpedantic -msse3

INCLUDES = -I.

BIN_DIR = bin

SOURCES_DIR = src
SOURCES  = $(shell cd $(SOURCES_DIR) && find ./ -type f -name '*.cpp' | sed 's:^\./::')

OBJECTS_DIR = obj
OBJECTS  = $(SOURCES:%.cpp=$(OBJECTS_DIR)/%.o)

LIBS     = -lSDL2

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) -o $@ $^ $(LIBS)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(BIN_DIR)/
	rm -rf $(OBJECTS_DIR)/

TEST_TARGET  = $(BIN_DIR)/test.elf

TEST_DIR     = test
TEST_SOURCES_FILTER = main.cpp
TEST_SOURCES = $(shell find $(TEST_DIR)/ -type f -name '*.cpp' | sed 's:^\./::')

TEST_OBJECTS_FILTER = $(TEST_SOURCES_FILTER:%.cpp=$(OBJECTS_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=$(OBJECTS_DIR)/%.o) $(filter-out $(TEST_OBJECTS_FILTER), $(OBJECTS))

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	mkdir -p $(@D)
	$(CXX) -o $@ $^ $(LIBS)
	$@

$(OBJECTS_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

