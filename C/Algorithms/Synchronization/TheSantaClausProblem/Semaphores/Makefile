CC = gcc
CFLAGS = -Wall
LDLIBS = -lpthread
SOURCES = reindeer.c santa.c elf.c draw.c main.c
OBJECTS = $(SOURCES: .c = .o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o *~ main
