CC = g++
CFLAGS =-c -Wall
LDFLAGS =-lsfml-system -lsfml-graphics -lsfml-window -llua -lfmodex -lfmodevent
SOURCES = main.cpp \
	Player.cpp \
	MachinePart.cpp \
	LuaMachine.cpp \
	LevelNode.cpp \
	GameObject.cpp \
	audio/global_audio.cpp \
	debug/log.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJDIR = obj
EXECUTABLE = bin/Disquiet

vpath %.o obj

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(OBJDIR)/,$(OBJECTS)) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

.PHONY: clean
clean:
	rm obj/*.o
	rm bin/*