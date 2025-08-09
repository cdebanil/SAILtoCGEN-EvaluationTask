CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude  # -Iinclude tells compiler where headers are

SOURCES = src/main.cpp src/helpers.cpp src/parser.cpp src/sexpr.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = bin/jsontosexp

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)