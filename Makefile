TARGET   = P1.elf

CXX ?= g++

CXXFLAGS = $(INCLUDES) -std=c++11 -Wall -Wextra -Wpedantic -msse3

INCLUDES = -I$(SOURCES_DIR)

SOURCES_DIR = src/

SOURCES  = common.cpp \
           core/core.cpp \
           core/memory/allocator.cpp \
           core/memory/linearAllocator.cpp \
           core/memory/stackAllocator.cpp \
           editor/editor.cpp \
           game/game.cpp \
           main.cpp \
           photon/glContext.cpp \
           photon/photon.cpp \
           photon/scene.cpp \
           photon/window.cpp

OBJECTS_DIR = obj/

OBJECTS  = $(SOURCES:%.cpp=$(OBJECTS_DIR)%.o)

LIBS     = -lSDL2

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test:
	./test.sh

clean:
	rm -f  $(TARGET)
	rm -rf $(OBJECTS_DIR)
