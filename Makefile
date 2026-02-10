# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/tombstone

# Explicitly list source files (Safer for now)
SRCS = $(SRC_DIR)/main.cpp

# Define Object files based on Source files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Main build target
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build successful! Run with: ./$(TARGET)"

# Rule to compile .cpp to .o
# NOTE: The indented lines below MUST use a TAB character, not spaces.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean command
clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean
