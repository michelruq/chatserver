CC = g++
CFLAGS= -c -Wall
SOURCES=main.cpp buffer.cpp
LIB_NAME=mysqlclient
LIB_PATH=/usr/lib/x86-64-linux-gnu
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -L$(LIB_PATH) -l$(LIB_NAME) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *.o server
