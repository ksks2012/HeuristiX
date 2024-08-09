# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -g

# Directories
SRCDIR = ..
BINDIR = $(SRCDIR)/cmd
INCDIR = $(SRCDIR)/header $(SRCDIR)/algo $(SRCDIR)/utils

# Files
MAIN_SRC = $(SRCDIR)/main.cpp
FUNC_SRC = $(SRCDIR)/benchmark.cpp
ALGO_SRC = $(SRCDIR)/algo/algo.cpp
UTILS_SRC = $(SRCDIR)/utils/utils.cpp

OBJS = $(MAIN_SRC:.cpp=.o) $(ALGO_SRC:.cpp=.o) $(UTILS_SRC:.cpp=.o)
FUNC_OBJS = $(FUNC_SRC:.cpp=.o) $(UTILS_SRC:.cpp=.o)

# Output executable
TARGET = $(BINDIR)/tsp_solver
FUNC_TARGET = $(BINDIR)/benchmark

# Define include directories
INCLUDES = $(foreach d, $(INCDIR), -I$d)

# Rules
all: $(TARGET)

func: $(FUNC_TARGET)

$(FUNC_TARGET): $(FUNC_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(SRCDIR)/*.o

.PHONY: all clean
