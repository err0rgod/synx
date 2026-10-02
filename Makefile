CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra 
TARGET = synx

.PHONY: all clean run 

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean: 
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)