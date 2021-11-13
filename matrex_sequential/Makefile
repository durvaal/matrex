all: clean_matrex_sequential_exec matrix_class methods main matrex_sequential clean

matrix_class: modules/matrix_class.cpp
	g++ -Wall -c modules/matrix_class.cpp -fsanitize=address -g

methods: modules/methods.cpp
	g++ -Wall -c modules/methods.cpp -fsanitize=address -g

main: main.cpp
	g++ -Wall -c main.cpp -fsanitize=address -g

matrex_sequential:
	g++ matrix_class.o methods.o main.o -o matrex_sequential -fsanitize=address -static-libasan

clean_matrex_sequential_exec:
	rm -f matrex_sequential

clean:
	rm -f matrix_class.o methods.o main.o