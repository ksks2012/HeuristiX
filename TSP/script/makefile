# Define the compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -g

# Define directories
SRCDIR = ..
BINDIR = $(SRCDIR)/cmd
INCDIR = $(SRCDIR)/header $(SRCDIR)/algo $(SRCDIR)/algo/SA $(SRCDIR)/algo/tabu_search $(SRCDIR)/utils $(SRCDIR)/utils/type

# Define source files
MAIN_SRC = $(SRCDIR)/main.cpp
ALGO_SRC = $(SRCDIR)/algo/algo.cpp $(SRCDIR)/algo/SA/SA.cpp $(SRCDIR)/algo/tabu_search/tabu_search.cpp
UTILS_SRC = $(SRCDIR)/utils/utils.cpp

# Define object files
OBJS = $(MAIN_SRC:.cpp=.o) $(ALGO_SRC:.cpp=.o) $(UTILS_SRC:.cpp=.o) $(DATA_READER_OBJ)

# Define the target binary
TARGET = $(BINDIR)/tsp_solver

# Define include directories
INCLUDES = $(foreach d, $(INCDIR), -I$d)

# Default rule
all: $(TARGET)

# Compile each cpp file into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Clean object files and binary
clean:
	rm -f $(SRCDIR)/main.o $(SRCDIR)/algo/*.o $(SRCDIR)/algo/SA/*.o $(SRCDIR)/utils/*.o $(TARGET)

# Phony targets
.PHONY: all clean
