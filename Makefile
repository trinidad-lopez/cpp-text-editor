#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g
GTEST_DIR = C:/dev/c++/googletest/googletest

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

# define test directory
TEST	:= test

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
TESTS	:= test.exe
LGTEST	:= libgtest.a
GMTESTO	:= gtest-main.o
GTESTO	:= gtest-all.o
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
TESTDIRS	:= $(TEST)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
TESTS	:= test
LGTEST	:= libgtest
GMTESTO	:= gtest-main
GTESTO	:= gtest-all
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
TESTDIRS	:= $(shell find $(TEST) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
# GTEST_I		:= $(patsubst %,-I%, $(GTEST_DIR:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
LIBGTEST	:= $(OUTPUT)/tests/$(LGTEST)

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
CORE		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)/core))

# define the test source files
TESTSRC		:= $(wildcard $(patsubst %,%/*.cpp, $(TESTDIRS)))

# define the C object files
MAINOBJ			:=$(patsubst $(SRC)/%.cpp,$(OUTPUT)/app/%.o, $(SOURCES))
COREOBJ			:= $(patsubst $(SRC)/core/%.cpp,$(OUTPUT)/app/core/%.o, $(CORE))
TESTOBJECTS		:= $(patsubst $(TEST)/%.cpp,$(OUTPUT)/tests/%.o, $(TESTSRC))
GTESTMAINOBJECT	:= $(OUTPUT)/tests/$(GMTESTO)
GTESTALLOBJECT	:= $(OUTPUT)/tests/$(GTESTO)

# define the dependency output files
MDEPS		:= $(MAINOBJ:.o=.d)
CDEPS		:= $(COREOBJ:.o=.d)
TDEPS		:= $(TESTOBJECTS:.o=.d)

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(OUTPUT)/app/$(MAIN)
OUTPUTTEST	:= $(OUTPUT)/tests/$(TESTS)

.PHONY: all
all: app build_test
	@echo Executing 'all' complete!

.PHONY: app
app: $(OUTPUTMAIN)
	@echo Building 'app' complete!

$(OUTPUT):
	$(MD) $(call FIXPATH, $@)

$(OUTPUT)/app:
	$(MD) $(call FIXPATH, $@)

$(OUTPUT)/app/core:
	$(MD) $(call FIXPATH, $@)

$(OUTPUT)/tests:
	$(MD) $(call FIXPATH, $@)


$(OUTPUTMAIN): $(MAINOBJ) $(COREOBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(MAINOBJ) $(COREOBJ) $(LFLAGS) $(LIBS)

# include all .d files
-include $(MDEPS)
-include $(CDEPS)
-include $(TDEPS)

# this is a suffix replacement rule for building .o's and .d's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# -MMD generates dependency output files same name as the .o file
# (see the gnu make manual section about automatic variables)
$(OUTPUT)/app/%.o: $(SRC)/%.cpp | $(OUTPUT)/app
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $<  -o $@

$(OUTPUT)/app/core/%.o: $(SRC)/core/%.cpp | $(OUTPUT)/app/core
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $<  -o $@

$(OUTPUT)/tests/%.o: $(TEST)/%.cpp	| $(OUTPUT)/tests
	$(CXX) $(CXXFLAGS) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) $(INCLUDES) -c -MMD $<  -o $@

.PHONY: clean
clean:
	$(RM) $(call FIXPATH, $(OUTPUTMAIN))
	$(RM) $(call FIXPATH, $(OUTPUTTEST))
	$(RM) $(call FIXPATH, $(LIBGTEST))
	$(RM) $(call FIXPATH, $(GTESTALLOBJECT))
	$(RM) $(call FIXPATH, $(GTESTMAINOBJECT))
	$(RM) $(call FIXPATH, $(MAINOBJ))
	$(RM) $(call FIXPATH, $(COREOBJ))
	$(RM) $(call FIXPATH, $(TESTOBJECTS))
	$(RM) $(call FIXPATH, $(MDEPS))
	$(RM) $(call FIXPATH, $(CDEPS))
	$(RM) $(call FIXPATH, $(TDEPS))
	@echo Cleanup complete!

.PHONY: run
run: $(OUTPUTTEST) $(OUTPUTMAIN)
	./$(OUTPUTTEST)
	./$(OUTPUTMAIN)
	@echo Executing 'run' complete!

.PHONY: run_app
run_app: $(OUTPUTMAIN)
	./$(OUTPUTMAIN)
	@echo Executing 'run_app' complete!

.PHONY: run_test
run_test: $(OUTPUTTEST)
	./$(OUTPUTTEST)
	@echo Executing 'run_test' complete!

.PHONY: build_test
build_test: $(OUTPUTTEST)
	@echo Building 'tests' complete!

$(OUTPUTTEST): $(TESTOBJECTS) $(LIBGTEST) $(COREOBJ) $(GTESTMAINOBJECT)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS) $(LIBS)

$(LIBGTEST): $(GTESTALLOBJECT)
	ar rv $@ $<

$(GTESTALLOBJECT): $(GTEST_DIR)/src/gtest-all.cc | $(OUTPUT)/tests
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread $(CXXFLAGS) -c $< -o $@

$(GTESTMAINOBJECT): $(GTEST_DIR)/src/gtest_main.cc | $(OUTPUT)/tests
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread $(CXXFLAGS) -c $< -o $@