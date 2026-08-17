CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

SRC_DIR = src
DRIVER_DIR = driver
BUILD_DIR = build

TARGET = $(BUILD_DIR)/assignment_03

SRC_FILES = \
	$(SRC_DIR)/MST.cpp \
	../assignment_02/src/CSR.cpp \
	$(DRIVER_DIR)/main.cpp

OBJ_FILES = \
	$(BUILD_DIR)/MST.o \
	$(BUILD_DIR)/CSR.o \
	$(BUILD_DIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/MST.o: $(SRC_DIR)/MST.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Reuse the CSR implementation from Assignment 2.
# Assignment 3 does not copy or reimplement the CSR conversion.
$(BUILD_DIR)/CSR.o: ../assignment_02/src/CSR.cpp ../assignment_02/src/CSR.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(DRIVER_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
