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
	rm -f $(TARGET) assignment_01.exe assignment_02.exe assignment_03.exe assignment_04.exe
	rm -rf assignment_01/build assignment_02/build assignment_03/build assignment_04/build