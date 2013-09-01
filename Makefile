# Based on Makefile from <URL: http://hak5.org/forums/index.php?showtopic=2077&p=27959 >

PROGRAM = WtPhidgetManager

############# Main application #################
all:    $(PROGRAM)
.PHONY: all

# source files
DEBUG_INFO = YES
SOURCES = $(shell find . -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(OBJECTS:.o=.dep)

######## compiler- and linker settings #########
CXX = g++
CXXFLAGS = -I/usr/include -W -Wall -Werror -pipe
LIBSFLAGS = -L/usr/lib -lphidget21 -lwt -lwthttp -lboost_signals -lpthread
ifdef DEBUG_INFO
 CXXFLAGS += -g
else
 CXXFLAGS += -O3
endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

%.dep: %.cpp
	$(CXX) $(CXXFLAGS) -MM $< -MT $(<:.cpp=.o) > $@


############# Main application #################
$(PROGRAM):	$(OBJECTS) $(DEPS)
	$(CXX) -o $@ $(OBJECTS) $(LIBSFLAGS)

################ Dependencies ##################
ifneq ($(MAKECMDGOALS),clean)
include $(DEPS)
endif

################### Clean ######################
clean:
	find . -name '*~' -delete
	-rm -f $(PROGRAM) $(OBJECTS) $(DEPS)

install:
	strip -s $(PROGRAM) && cp $(PROGRAM) /usr/local/bin/
