CC	= gcc
CXX	= g++

OBJECTS		= glad.o glManager.o display.o shader.o main.o
CXX_FLAGS	= -std=c++11
LIBS		= `pkg-config --libs glfw3` -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: build trash

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(LIBS) -o main

glad.o: Graphics/glad.c
	$(CC) -c Graphics/glad.c

glManager.o: Graphics/glManager.cpp
	$(CXX) $(CXX_FLAGS) -c Graphics/glManager.cpp

display.o: Graphics/display.cpp
	$(CXX) $(CXX_FLAGS) -c Graphics/display.cpp

shader.o: Graphics/shader.cpp
	$(CXX) $(CXX_FLAGS) -c Graphics/shader.cpp

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c main.cpp

trash:
	rm -rf *.o

clean:
	rm -rf *.o main
