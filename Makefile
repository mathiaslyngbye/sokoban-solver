TARGET_EXEC = sokoban-solver.out

BUILD_DIR = ./build
SRC_DIRS = ./src

SRCS = $(shell find $(SRC_DIRS) -name *.cpp)
#OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS = $(patsubst %,$(BUILD_DIR)/%,$(SRCS:.cpp=.cpp.o))

INC_DIRS = include
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

CPP = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
CPPFLAGS += $(INC_FLAGS)

# c++ objects
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CPP) $(OBJS) -o $@ 

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CPP) $(CPPFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)


MKDIR_P ?= mkdir -p
