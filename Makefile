TARGET   = P1

COMPILER = g++
CXXFLAGS = -std=c++11 -Wall

LIBS     = -lSDL2

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

OBJECTS  = $(SOURCES:.cpp=.o)

OBJECTS_DIR = obj/

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(COMPILER) -o $(TARGET) $(addprefix $(OBJECTS_DIR), $(OBJECTS)) $(LIBS)

%.o: %.cpp
	@mkdir -p $(dir $(OBJECTS_DIR)$@)
	$(COMPILER) $(CXXFLAGS) $(INCLUDES) -o $(OBJECTS_DIR)$@ -c $<

clean:
	rm -f  $(TARGET)
	rm -rf $(OBJECTS_DIR)
	rm -f  *~
