# Makefile for CPU Instruction Set Simulator

CXX = g++
CXXFLAGS = -Wall -O2
TARGET = cpu_simpulator
SRC = cpu_simpulator.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	del $(TARGET).exe
