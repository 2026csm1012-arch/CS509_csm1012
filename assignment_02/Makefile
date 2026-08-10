CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc -O3

SRC_DIR = src
DRIVER_DIR = driver
BUILD_DIR = build
TARGET = $(BUILD_DIR)/assignment_02.exe

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(DRIVER_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp)) \
       $(patsubst $(DRIVER_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(DRIVER_DIR)/*.cpp))

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(DRIVER_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean