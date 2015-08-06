TARGET   = P1

COMPILER = g++

CXXFLAGS = $(INCLUDES) -std=c++11 -Wall -Wextra -Wpedantic -msse3

INCLUDES = -I./

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
	$(COMPILER) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f  $(TARGET)
	rm -rf $(OBJECTS_DIR)

test:
	./test.sh
