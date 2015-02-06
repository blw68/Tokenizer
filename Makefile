CC = gcc
CCFLAGS = -g -Wall

tokenizer: tokenizer.o
	$(CC) $(CCFLAGS) tokenizer.o -o tokenizer

tokenizer.o: tokenizer.c
	$(CC) $(CCFLAGS) -c tokenizer.c

clean:
	rm -f *.o tokenizer
