# (g)make file for C++11+ Exception Support Article examples

# Tools
CC := gcc
CXX := g++

# Tool flags
CFLAGS := -Wall -Wextra -pedantic  -pthread 
CXXFLAGS += -Wall -Wextra -pedantic -std=c++11 -pthread
LDFLAGS += -pthread

# The following four programs are single file affairs with
# no non-library includes
EXCEPT_RAISING := cxx11_exception_raising_examples
EXCEPT_RAISING_OBJ := $(EXCEPT_RAISING).o

EXCEPTION_PTR := cxx11_std_exception_ptr_etc_example
EXCEPTION_PTR_OBJ := $(EXCEPTION_PTR).o

NESTED_EXCEPTION := cxx11_nested_exception_usage_example
NESTED_EXCEPTION_OBJ := $(NESTED_EXCEPTION).o

CUSTOM_ERRC := cxx11_custom_error_code_example
CUSTOM_ERRC_OBJ := $(CUSTOM_ERRC).o

# The next three projects use a common C API and main but different
# C++ API implementations:
COMMON_CATCH_MAIN_OBJ:= cxx11_common_catch_clause_eg_main.o
CATCH_CLAUSE_MOTIVATING := cxx11_common_catch_clause_motivating_example
CATCH_CLAUSE_MOTIVATING_OBJ := $(CATCH_CLAUSE_MOTIVATING).o $(COMMON_CATCH_MAIN_OBJ)

CATCH_CLAUSE_AROUND := cxx11_common_catch_clause_exec_around_example
CATCH_CLAUSE_AROUND_OBJ := $(CATCH_CLAUSE_AROUND).o $(COMMON_CATCH_MAIN_OBJ)

CATCH_CLAUSE := cxx11_common_catch_clause_example
CATCH_CLAUSE_OBJ := $(CATCH_CLAUSE).o $(COMMON_CATCH_MAIN_OBJ)

all : $(EXCEPT_RAISING) \
			$(EXCEPTION_PTR) \
			$(NESTED_EXCEPTION) \
			$(CUSTOM_ERRC) \
			$(CATCH_CLAUSE_MOTIVATING) \
			$(CATCH_CLAUSE_AROUND) \
			$(CATCH_CLAUSE)
.PHONY: all

clean : tidy
	-rm $(EXCEPT_RAISING)
	-rm $(EXCEPTION_PTR)
	-rm $(NESTED_EXCEPTION)
	-rm $(CUSTOM_ERRC)
	-rm $(CATCH_CLAUSE_MOTIVATING)
	-rm $(CATCH_CLAUSE_AROUND)
	-rm $(CATCH_CLAUSE)
.PHONY: clean

tidy :
	-rm *.o
.PHONY: tidy

$(EXCEPT_RAISING): $(EXCEPT_RAISING_OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(EXCEPTION_PTR): $(EXCEPTION_PTR_OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(NESTED_EXCEPTION): $(NESTED_EXCEPTION_OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CUSTOM_ERRC): $(CUSTOM_ERRC_OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

COMMON_CATCH_API_HDR := cxx11_common_catch_clause_eg_api.h

$(CATCH_CLAUSE): $(CATCH_CLAUSE_OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CATCH_CLAUSE_AROUND): $(CATCH_CLAUSE_AROUND_OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CATCH_CLAUSE_MOTIVATING): $(CATCH_CLAUSE_MOTIVATING_OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CATCH_CLAUSE_AROUND).o: $(CATCH_CLAUSE_AROUND).cpp $(COMMON_CATCH_API_HDR)

$(CATCH_CLAUSE_MOTIVATING).o: $(CATCH_CLAUSE_MOTIVATING).cpp $(COMMON_CATCH_API_HDR)

$(COMMON_CATCH_MAIN_OBJ): $(COMMON_CATCH_MAIN_OBJ:.o=.c) $(COMMON_CATCH_API_HDR)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

