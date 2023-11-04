CXX = g++
CXXFLAGS = -std=c++11 -Wall
SOURCES = QuartenarySearchTree.cpp
EXECUTABLE = QuartenarySearchTree

$(EXECUTABLE): $(SOURCES)
        $(CXX) $(CXXFLAGS) -o $@ $^

clean:
        rm -f $(EXECUTABLE)