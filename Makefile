CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

SOURCES = src/main.cpp src/helpers.cpp src/parser.cpp src/sexpr.cpp
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))
EXECUTABLE = bin/jsontosexp

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(OBJECTS) -o $@

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)