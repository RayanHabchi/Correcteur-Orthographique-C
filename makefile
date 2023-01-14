CC = gcc
CFLAGS = -Wall -ansi
LDFLAGS = -lMLV
EXEC = correcteur_2
OBJ = correcteur_2.o listes.o ATR.o Levenshtein.o ArbreBK.o

all: correcteur_2 clean

correcteur_2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
correcteur_2.o: correcteur_2.c listes.h ATR.h Levenshtein.h ArbreBK.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)
	
listes.o: listes.c ATR.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

ATR.o: ATR.c listes.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

Levenshtein.o: Levenshtein.c 
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

ArbreBK.o: ArbreBK.c listes.h Levenshtein.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o