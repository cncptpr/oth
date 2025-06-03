run: aufgabe1
	./aufgabe1

aufgabe1: aufgabe1.o  aufgabe1-lib.o
	g++ -o aufgabe1 aufgabe1.o  aufgabe1-lib.o	

aufgabe1.o: aufgabe1.cpp aufgabe1.h
	g++ -c aufgabe1.cpp

aufgabe1-lib.o: aufgabe1-lib.cpp aufgabe1.h
	g++ -c aufgabe1-lib.cpp
	
# # Compiler
# CXX = g++

# # Compiler flags
# CXXFLAGS = -Wall -g

# # Target executable
# TARGET = main

# # For deleting the target
# TARGET_DEL = main.exe

# # Source files
# SRCS = aufgabe1.cpp aufgabe1-lib.cpp

# # Object files
# OBJS = $(SRCS:.cpp=.o)

# # Default rule to build and run the executable
# all: $(TARGET) run

# # Rule to link object files into the target executable
# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# # Rule to compile .cpp files into .o files
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Rule to run the executable
# run: $(TARGET)
# 	$(TARGET)

# # Clean rule to remove generated files
# clean:
# 	del $(TARGET_DEL) $(OBJS)


