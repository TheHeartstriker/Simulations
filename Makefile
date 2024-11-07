# Compiler and flags
CXX := g++
CXXFLAGS := -I SDL/include -I src -L SDL/lib

# Libraries
LIBS := -lmingw32 -lSDL2main -lSDL2

# Source files
SRC := main.cpp src/Window/Window.cpp src/Circle.cpp

# Output executable
OUT := main

# Build target
all:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LIBS)