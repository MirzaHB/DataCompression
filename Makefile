# compiler and flags
CC = gcc
CFLAGS = -Wall -std=c11

# executable name
TARGET = compressProgram

# source files
SRCS = main.c compression.c

# create object files from source files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
