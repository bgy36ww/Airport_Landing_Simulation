LDFLAGS=
SOURCES=main.cpp Event_List.cpp dist_gen.cpp
CFLAGS=-c -Wall -std=c++11
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=run

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	g++ $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
