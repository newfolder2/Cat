CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
CAT= s21_cat.c

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(CAT) -o s21_cat

test:
	chmod 777 integration_tests.sh
	./integration_tests.sh

clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o *.txt

rebuild:
	make clean
	make all
	rm -rf  *.o *.a

# done
