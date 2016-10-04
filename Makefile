PROGNAME ?= test

CXX := g++ -std=c++11
CXXFLAGS := -g -O0

SOURCES := $(wildcard *.cpp)

BUILDDIR := build

DEPENDS := $(patsubst %.cpp,$(BUILDDIR)/%.d,$(SOURCES))
OBJS := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SOURCES))

-include $(DEPENDS)

$(BUILDDIR)/:
	mkdir -p $@

# For every file foo.cpp, generate the dependencies for build/foo.o
# file into build/foo.d. Note that build/foo.d itself will have the same
# dependency as build/foo.o. Thus build/foo.d will look something like:
#
# build/foo.o build/foo.d: foo.cpp incfile1.h incfile2.h
#
# Notice both build/foo.o and build/foo.d on the LHS. This handles the case
# when the dependency needs to change because a header file got modified
# and the dependency of the CPP file changes without any change to the CPP
# file itself.
#
# Also note the "order only pre-requisite" on the build-directory existing.
# This ensures that the build directory is available before genering the .d
# files, but if the time stamp of the build directory changes, it does not
# force the .d file to get regenrated. If this were a stand pre-requisite,
# then every time a .d file changes, it would "dirty" all the .o and .d
# files. This is because in Linux, modifiying a file inside a directory
# also modifies the time-stamp of the containing directory.
$(BUILDDIR)/%.d : %.cpp | $(BUILDDIR)/
	@echo "Regenerating $@"
	@mkdir -p $(BUILDDIR)
	@$(CXX) -MM $< \
	    | sed 's/\(\w\+\).o/$(BUILDDIR)\/\1.o $(BUILDDIR)\/\1.d/' > $@

$(BUILDDIR)/%.o : %.cpp | $(BUILDDIR)/
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.DEFAULT_GOAL := $(PROGNAME)
$(PROGNAME): $(OBJS)
	g++ -o $@ $(OBJS)

.PHONY : clean
clean:
	\rm -f $(OBJS) $(DEPENDS) $(PROGNAME)

.PHONY : distclean
distclean: clean
	\rm -rf build 

