CC = gcc

SOURCES = matrix.c matrix_operations.c matrix_file_io.o example.c
HEADERS = matrix.h

TARGET = example
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o: %.c $(HEADERS)
	$(CC) -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)
