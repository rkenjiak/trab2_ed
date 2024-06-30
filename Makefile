#TRACE=NDEBUG
CFLAGS=

bin/saida: bin/main.o bin/problem.o bin/set.o bin/linkedlist.o bin/hash.o bin/avl.o
	gcc $(CFLAGS) $(LDFLAGS) -o bin/saida bin/main.o bin/problem.o bin/set.o bin/linkedlist.o bin/hash.o bin/avl.o

bin/main.o: src/main.c
	gcc $(CFLAGS) -c -o bin/main.o src/main.c

bin/problem.o: src/problem.c include/problem.h
	gcc $(CFLAGS) -c -o bin/problem.o src/problem.c

bin/set.o: src/set.c include/set.h
	gcc $(CFLAGS) -c -o bin/set.o src/set.c

bin/linkedlist.o: src/linkedlist.c include/linkedlist.h
	gcc $(CFLAGS) -c -o bin/linkedlist.o src/linkedlist.c

bin/hash.o: src/hash.c include/hash.h
	gcc $(CFLAGS) -c -o bin/hash.o src/hash.c

bin/avl.o: src/avl.c include/avl.h
	gcc $(CFLAGS) -c -o bin/avl.o src/avl.c

.PHONY: clean

clean:
	rm -f bin/*.o bin/saida