# Binary name
TARGET_EXEC	= sokoban-solver

#  directories
BUILD_DIR = ./build
SRC_DIRS  = ./src
INC_DIRS  = include

# Files
SRCS = $(shell find $(SRC_DIRS) -name *.cpp)
OBJS = $(SRCS:$(SRC_DIRS)/%.cpp=$(BUILD_DIR)/%.cpp.o)

# Compile settings 
CPP 	  = g++
CPPFLAGS  = -std=c++17 -O2 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
INC_FLAGS = $(addprefix -I,$(INC_DIRS))
CPPFLAGS += $(INC_FLAGS)

# C++ objects
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CPP) $(OBJS) -o $@ 

# C++ source
$(BUILD_DIR)/%.cpp.o: $(SRC_DIRS)/%.cpp $(INC_DIRS)/*
	$(MKDIR_P) $(dir $@)
	$(CPP) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
