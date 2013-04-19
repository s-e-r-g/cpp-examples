CC=g++
CFLAGS=-c -std=c++11 -Wall -W -pedantic -O2 -pthread
LDFLAGS=-lpthread

SOURCES=ping-pong.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ping-pong

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

test: all
	./$(EXECUTABLE)

