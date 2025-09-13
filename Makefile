inverted_search.out : main.o operation.o validate.o utility.o create_database.o
	gcc -Wall -Wextra -g -o inverted_search.out main.o operation.o validate.o utility.o create_database.o

main.o : main.c inverted_search.h
	gcc -Wall -Wextra -g -c main.c -o main.o

operation.o : operation.c inverted_search.h
	gcc -Wall -Wextra -g -c operation.c -o operation.o

validate.o : validate.c inverted_search.h
	gcc -Wall -Wextra -g -c validate.c -o validate.o

utility.o : utility.c inverted_search.h
	gcc -Wall -Wextra -g -c utility.c -o utility.o

create_database.o : create_database.c inverted_search.h
	gcc -Wall -Wextra -g -c create_database.c -o create_database.o

run: inverted_search.out
	./inverted_search.out file1.txt file2.txt

clean:
	rm -f main.o operation.o validate.o utility.o create_database.o inverted_search.out
