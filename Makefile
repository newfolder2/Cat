CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
CAT= cat.c

all: cat

s21_cat:
	$(CC) $(CFLAGS) $(CAT) -o cat

test:
	chmod 777 tests.sh
	./tests.sh

clean:
	rm -rf cat
	rm -rf *.a *.out *.o *.txt

rebuild:
	make clean
	make all
	rm -rf  *.o *.a

# done
