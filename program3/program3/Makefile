RM=rm -f
CPPFLAGS=-g -pthread
LDFLAGS=-g
LDLIBS=

SRCS=nodedata.cpp lab3.cpp graphm.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: program3

program3: $(OBJS)
	g++ $(LDFLAGS) -o program3 $(OBJS) $(LDLIBS)

nodedata.o: nodedata.cpp nodedata.h
	g++ $(CPPFLAGS) -c nodedata.cpp

lab3.o: lab3.cpp
	g++ $(CPPFLAGS) -c lab3.cpp

graphm.o: graphm.cpp graphm.h
	g++ $(CPPFLAGS) -c graphm.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) program3
