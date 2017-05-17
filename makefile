CC = gcc
#CFLAGS = -W -Wall
TARGET = main
OBJECTS = main.o mnist-read.o mnist-1lnn.o

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

clean :
	del /Q $(OBJECTS) $(TARGET).exe

mnist-read.o : mnist-read.h mnist-read.c
mnist-1lnn.o : mnist-read.h mnist-read.c mnist-1lnn.h mnist-1lnn.c
main.o : main.h main.c