CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = wrapper
SRC = wrapper.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)