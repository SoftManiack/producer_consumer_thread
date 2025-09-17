CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread  # Добавьте -pthread здесь
TARGET = program
SOURCES = doubly_linked_list.c main.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
# make     
# make run 
# make cleannake