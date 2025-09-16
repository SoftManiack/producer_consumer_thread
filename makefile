CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c99
TARGET = producer_consumer
OBJS = main.o producer_consumer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c producer_consumer.h
	$(CC) $(CFLAGS) -c main.c

producer_consumer.o: producer_consumer.c producer_consumer.h
	$(CC) $(CFLAGS) -c producer_consumer.c

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean