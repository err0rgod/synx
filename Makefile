CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = synx

# Automatically detect all C++ source and header files
SRCS = $(wildcard *.cpp)
HDRS = $(wildcard *.hpp)

.PHONY: all clean run

all: $(TARGET)

# If ANY .cpp or .hpp file changes, rebuild the binary using all source files!

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)