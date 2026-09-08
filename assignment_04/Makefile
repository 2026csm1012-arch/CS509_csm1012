CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

TARGET = graph_runner

SRC = driver/main.cpp \
      src/CSR.cpp \
      src/graph_io.cpp \
      src/vertex_coloring.cpp \
      src/pagerank.cpp \
      src/output.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
