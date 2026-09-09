CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc -O3

SRC_DIR = src
DRIVER_DIR = driver
BUILD_DIR = build

TARGET = assignment_02.exe


# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
DRIVER_FILES = $(wildcard $(DRIVER_DIR)/*.cpp)

# Object files
SRC_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/src/%.o,$(SRC_FILES))
DRIVER_OBJECTS = $(patsubst $(DRIVER_DIR)/%.cpp,$(BUILD_DIR)/driver/%.o,$(DRIVER_FILES))

OBJECTS = $(SRC_OBJECTS) $(DRIVER_OBJECTS)


# Default target
all: $(TARGET)


# Create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)


# Compile src files
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)/src
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Compile driver files
$(BUILD_DIR)/driver/%.o: $(DRIVER_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)/driver
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Remove compiled files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)


.PHONY: all clean