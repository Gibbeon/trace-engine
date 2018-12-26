MKFILE_PATH:= $(abspath $(lastword $(MAKEFILE_LIST)))
PARENT_PATH:=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
CURRENT_DIR:= $(notdir $(patsubst %/,%,$(dir $(MKFILE_PATH))))
PARENT_DIR:= $(notdir $(patsubst %/,%,$(dir $(PARENT_PATH))))

TARGET_EXEC = $(basename $(PARENT_DIR))_$(CURRENT_DIR).exe
BUILD_DIR ?= ./build
INSTALL_DIR ?= ./bin
SRC_DIRS ?= ./src
INC_DIRS ?= ./include ./../include ./../ted3d/lib/d3d12/include

INCS := $(INC_DIRS) 
SRCS := $(shell find $(SRC_DIRS) -name "*.cpp" -or -name "*.c" -or -name "*.s")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CC=g++ -march=x86-64 -mwindows
CXX=g++ -march=x86-64 -mwindows
RM=rm -f
CPPFLAGS=-std=c++17 -O0 -g
#LDFLAGS=
LDLIBS=./../ted3d/lib/d3d12/bin/x64/d3d12.lib

#INC_DIRS ?= $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INCS))

CPPFLAGS += $(INC_FLAGS) -MMD -MP

build: $(BUILD_DIR)/$(TARGET_EXEC) install

run: build install
	$(INSTALL_DIR)/$(TARGET_EXEC)

install:
	@mkdir -p $(INSTALL_DIR)
	cp $(BUILD_DIR)/$(TARGET_EXEC) $(INSTALL_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(INSTALL_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p