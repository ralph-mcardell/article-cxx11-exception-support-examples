# (g)make file for C++11+ Exception Support Article examples

# Tools
CC := gcc
CXX := g++
MKDIR_ALL := mkdir -p
MK_TARGET_DIR = @$(MKDIR_ALL) $(@D)

# Tool flags
CFLAGS := -Wall -Wextra -pedantic  -pthread 
CXXFLAGS += -Wall -Wextra -pedantic -std=c++11 -pthread
LDFLAGS += -pthread

# Directories
SOURCE_DIR := src
BIN_DIR := bin
BUILD_DIR := build

# The following four programs are single file affairs with
# no non-library includes
EXCEPT_RAISING := cxx11_exception_raising_examples
EXCEPT_RAISING_BIN := $(BIN_DIR)/$(EXCEPT_RAISING)
EXCEPT_RAISING_OBJ := $(BUILD_DIR)/$(EXCEPT_RAISING).o

EXCEPTION_PTR := cxx11_std_exception_ptr_etc_example
EXCEPTION_PTR_BIN := $(BIN_DIR)/$(EXCEPTION_PTR)
EXCEPTION_PTR_OBJ := $(BUILD_DIR)/$(EXCEPTION_PTR).o

NESTED_EXCEPTION := cxx11_nested_exception_usage_example
NESTED_EXCEPTION_BIN := $(BIN_DIR)/$(NESTED_EXCEPTION)
NESTED_EXCEPTION_OBJ := $(BUILD_DIR)/$(NESTED_EXCEPTION).o

CUSTOM_ERRC := cxx11_custom_error_code_example
CUSTOM_ERRC_BIN := $(BIN_DIR)/$(CUSTOM_ERRC)
CUSTOM_ERRC_OBJ := $(BUILD_DIR)/$(CUSTOM_ERRC).o

# The next three projects use a common C API and main but different
# C++ API implementations:
COMMON_CATCH_MAIN:= cxx11_common_catch_clause_eg_main
COMMON_CATCH_MAIN_OBJ:= $(BUILD_DIR)/$(COMMON_CATCH_MAIN).o
COMMON_CATCH_MAIN_OBJ:= $(BUILD_DIR)/cxx11_common_catch_clause_eg_main.o
CATCH_CLAUSE_MOTIVATING := cxx11_common_catch_clause_motivating_example
CATCH_CLAUSE_MOTIVATING_BIN := $(BIN_DIR)/$(CATCH_CLAUSE_MOTIVATING)
CATCH_CLAUSE_MOTIVATING_OBJ := $(BUILD_DIR)/$(CATCH_CLAUSE_MOTIVATING).o $(COMMON_CATCH_MAIN_OBJ)

CATCH_CLAUSE_AROUND := cxx11_common_catch_clause_exec_around_example
CATCH_CLAUSE_AROUND_BIN := $(BIN_DIR)/$(CATCH_CLAUSE_AROUND)
CATCH_CLAUSE_AROUND_OBJ := $(BUILD_DIR)/$(CATCH_CLAUSE_AROUND).o $(COMMON_CATCH_MAIN_OBJ)

CATCH_CLAUSE := cxx11_common_catch_clause_example
CATCH_CLAUSE_BIN := $(BIN_DIR)/$(CATCH_CLAUSE)
CATCH_CLAUSE_OBJ := $(BUILD_DIR)/$(CATCH_CLAUSE).o $(COMMON_CATCH_MAIN_OBJ)

all : $(EXCEPT_RAISING_BIN) \
			$(EXCEPTION_PTR_BIN) \
			$(NESTED_EXCEPTION_BIN) \
			$(CUSTOM_ERRC_BIN) \
			$(CATCH_CLAUSE_MOTIVATING_BIN) \
			$(CATCH_CLAUSE_AROUND_BIN) \
			$(CATCH_CLAUSE_BIN)
.PHONY: all

clean : tidy
	-rm $(BIN_DIR)/*

.PHONY: clean

tidy :
	-rm $(BUILD_DIR)/*
.PHONY: tidy

$(EXCEPT_RAISING_BIN): $(EXCEPT_RAISING_OBJ)
	$(MK_TARGET_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(EXCEPTION_PTR_BIN): $(EXCEPTION_PTR_OBJ)
	$(MK_TARGET_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(NESTED_EXCEPTION_BIN): $(NESTED_EXCEPTION_OBJ)
	$(MK_TARGET_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CUSTOM_ERRC_BIN): $(CUSTOM_ERRC_OBJ)
	$(MK_TARGET_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

COMMON_CATCH_API_HDR := $(SOURCE_DIR)/cxx11_common_catch_clause_eg_api.h

$(CATCH_CLAUSE_BIN): $(CATCH_CLAUSE_OBJ)
	$(MK_TARGET_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CATCH_CLAUSE_AROUND_BIN): $(CATCH_CLAUSE_AROUND_OBJ)
	$(MK_TARGET_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CATCH_CLAUSE_MOTIVATING_BIN): $(CATCH_CLAUSE_MOTIVATING_OBJ)
	$(MK_TARGET_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/$(CATCH_CLAUSE_AROUND).o: $(SOURCE_DIR)/$(CATCH_CLAUSE_AROUND).cpp $(COMMON_CATCH_API_HDR)

$(BUILD_DIR)/$(CATCH_CLAUSE_MOTIVATING).o: $(SOURCE_DIR)/$(CATCH_CLAUSE_MOTIVATING).cpp $(COMMON_CATCH_API_HDR)

$(BUILD_DIR)/$(CATCH_CLAUSE).o: $(SOURCE_DIR)/$(CATCH_CLAUSE).cpp $(COMMON_CATCH_API_HDR)

$(COMMON_CATCH_MAIN_OBJ): $(SOURCE_DIR)/$(COMMON_CATCH_MAIN).c $(COMMON_CATCH_API_HDR)
	$(MK_TARGET_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(MK_TARGET_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

