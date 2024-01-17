# Compiler, flags and directories
CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11 -I $(INC)
TARGET = tp
SRCDIR = src

# Source files
SRC = $(wildcard $(SRCDIR)/*.cpp)
INC = include

all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRC)


# Run the program
run: $(TARGET)
	@./$(TARGET)	


# Clean rule the executable
clean:
	rm -f $(OBJ) $(TARGET) 