CC = gcc
CFLAGS = -Wall -g --std=c99
OBJECTS = main.o my_string.o unit_test vector.o node.o associative_array.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm string_driver $(OBJECTS) unit_test.o test_def.o
my_string.o: my_string.h status.h my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
unit_test.o: my_string.h status.h unit_test.h unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c unit_test.o
test_def.o: my_string.h status.h unit_test.h test_def.c
	$(CC) $(CFLAGS) -c test_def.c test_def.o
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
vector.o: my_string.h status.h vector.h vector.c
	$(CC) $(CFLAGS) -c vector.c -o vector.o 
node.o: my_string.h status.h vector.h node.h node.c
	$(CC) $(CFLAGS) -c node.c -o node.o
associative_array.o: my_string.h status.h vector.h node.h associative_array.h associative_array.c
	$(CC) $(CFLAGS) -c associative_array.c -o associative_array.o
