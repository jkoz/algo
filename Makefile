P=algo_test
CFLAGS=-g -Wall -O3 -std=c99
LDFLAGS=
CC=gcc
OBJS = list.o dlist.o clist.o stack.o queue.o set.o chtbl.o ohtbl.o bitree.o string_algo.o sort.o recursive.o


$(P): $(P).c libalgo.so
	$(CC) $(CFLAGS) $(LDFLAGS) $(P).c -o $(P) -L. -lalgo

recursive.o: recursive.h recursive.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC recursive.h recursive.c


list.o: list.h list.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC list.h list.c

dlist.o: dlist.h dlist.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC dlist.h dlist.c

clist.o: clist.h clist.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC clist.h clist.c

queue.o: queue.h queue.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC queue.h queue.c

stack.o: stack.h stack.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC stack.h stack.c

set.o: set.h set.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC set.h set.c

chtbl.o: chtbl.h chtbl.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC chtbl.h chtbl.c

ohtbl.o: ohtbl.h ohtbl.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC ohtbl.h ohtbl.c

bitree.o: bitree.h bitree.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -fPIC bitree.h bitree.c

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
