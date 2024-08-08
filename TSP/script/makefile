# 定義編譯器和標誌
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -g

# 定義目錄
SRCDIR = ..
BINDIR = $(SRCDIR)/cmd
INCDIR = $(SRCDIR)/header $(SRCDIR)/algo $(SRCDIR)/algo/SA $(SRCDIR)/utils $(SRCDIR)/utils/type

# 定義源文件
MAIN_SRC = $(SRCDIR)/main.cpp
ALGO_SRC = $(SRCDIR)/algo/algo.cpp $(SRCDIR)/algo/SA/SA.cpp
UTILS_SRC = $(SRCDIR)/utils/utils.cpp

# 定義目標文件
OBJS = $(MAIN_SRC:.cpp=.o) $(ALGO_SRC:.cpp=.o) $(UTILS_SRC:.cpp=.o) $(DATA_READER_OBJ)

# 定義輸出二進制文件
TARGET = $(BINDIR)/tsp_solver

# 定義包含目錄
INCLUDES = $(foreach d, $(INCDIR), -I$d)

# 默認規則
all: $(TARGET)

# 編譯每個cpp文件為object文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 將所有目標文件鏈接為最終二進制文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# 清理目標文件和二進制文件
clean:
	rm -f $(SRCDIR)/main.o $(SRCDIR)/algo/*.o $(SRCDIR)/algo/SA/*.o $(SRCDIR)/utils/*.o $(TARGET)

# Phony targets
.PHONY: all clean
