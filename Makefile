CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TARGET = rental_system

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all clean run help

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	./$(TARGET)

help:
	@echo "Available targets:"
	@echo "  make        - Build the rental_system executable"
	@echo "  make run    - Build and launch the application"
	@echo "  make clean  - Remove build artifacts and binary"

