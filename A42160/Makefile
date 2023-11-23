# Use this Makefile as a starting point for your A4.

# Keep the first rule with the target "all", and change the name of the
# dependencies to whatever you like. These represent the four main programs
# that a complete assignment should produce. If you haven't completed them
# all, remove any that don't exist.

# Then, change the remaining rules to build each of those main programs,
# based on the names of your source and header files. For the targets that
# link the programs, make sure the target name matches the first object
# file name, without the ".o". And for the targets that compile the object
# files, make sure that the .o target and the first .c dependency match.

# Use of variables is optional but it will make things easier!

CC=clang
CFLAGS=-Wall # -g -DNDEBUG

# The default goal is to build all four programs

all: test_multimap_a3 test_multimap_a4 test_kwic kwic

# Targets to link all four programs

test_multimap_a3: test_multimap_a3.o a4_tests.o multimap.o

test_multimap_a4: test_multimap_a4.o a4_tests.o multimap.o

test_kwic: test_kwic.o a4_tests.o kwic.o multimap.o

kwic: kwic.o a4_main.o multimap.o

# Targets to compile all object files

test_multimap_a3.o: test_multimap_a3.c a4_tests.h multimap.h boolean.h

test_multimap_a4.o: test_multimap_a4.c a4_tests.h multimap.h boolean.h

test_kwic.o: test_kwic.c a4_tests.h kwic.h multimap.h boolean.h

a4_tests.o: a4_tests.c a4_tests.h boolean.h

multimap.o: multimap.c multimap.h boolean.h

kwic.o: kwic.c kwic.h multimap.h boolean.h

a4_main.o: a4_main.c kwic.h multimap.h boolean.h

# Remove build products

clean:
	rm -f *.o test_multimap_a3 test_multimap_a4 test_kwic kwic
