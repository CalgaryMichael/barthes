CC = g++
BUILDPATH = build/barthes

CPPFLAGS = -O2 -g

OBJS = \
       src/config.o \
       src/handlers/file.o \
       src/handlers/input.o \
       src/handlers/screen.o \
       src/handlers/terminal.o \
       src/main.o

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

main: $(OBJS)
	$(CC) $(CPPFLAGS) -o $(BUILDPATH) $(OBJS)

all: main

clean:
	rm -f $(BUILDPATH)
	rm -f src/*.o
