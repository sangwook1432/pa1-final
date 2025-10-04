CC = gcc
OBJECTS = main.o operation1.o operation2.o operation3.o operation4.o utils.o

pa1: $(OBJECTS)
	$(CC) -o pa1 $(OBJECTS)

main.o: main.c myheader.h
	$(CC) -c main.c

operation1.o: operation1.c myheader.h
	$(CC) -c operation1.c

operation2.o: operation2.c myheader.h
	$(CC) -c operation2.c

operation3.o: operation3.c myheader.h
	$(CC) -c operation3.c

operation4.o: operation4.c myheader.h
	$(CC) -c operation4.c

utils.o: utils.c myheader.h
	$(CC) -c utils.c

clean:
	rm -f $(OBJECTS) pa1
