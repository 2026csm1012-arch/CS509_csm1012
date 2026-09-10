CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

# 1. Define the build folder (this was missing)
BUILD_DIR = build

# 2. Set the target executable path
TARGET =  assignment_04

# 3. List all your source files
SRC = driver/main.cpp \
      src/CSR.cpp \
      src/graph_io.cpp \
      src/vertex_coloring.cpp \
      src/pagerank.cpp \
      src/output.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)