CC = g++
BUILDPATH = build/barthes

CPPFLAGS = -O2 -g

OBJS = \
	src/main.o

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

main: $(OBJS)
	$(CC) $(CPPFLAGS) -o $(BUILDPATH) $(OBJS)

all: main

clean:
	rm -f $(BUILDPATH)
	rm -f src/*.o
