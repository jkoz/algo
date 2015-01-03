P=algo_test
CFLAGS=-g -Wall -O3 -std=c99
LDFLAGS=
CC=gcc
OBJS = list.o dlist.o string_algo.o sort.o recursive.o


$(P): $(P).c libalgo.so
	$(CC) $(CFLAGS) $(LDFLAGS) $(P).c -o $(P) -L. -lalgo

recursive.o: recursive.h recursive.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC recursive.h recursive.c

list.o: list.h list.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC list.h list.c

dlist.o: dlist.h dlist.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC dlist.h dlist.c

sort.o: sort.h sort.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC sort.h sort.c

string_algo.o: string_algo.h string_algo.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC string_algo.h string_algo.c

libalgo.so: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -fPIC -o libalgo.so $(OBJS)

clean:
	rm -f $(P)
	rm -f $(OBJS)
	rm -f libalgo.so
	rm -f *h.gch
