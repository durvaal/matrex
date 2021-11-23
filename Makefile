all: clean_exec matrix_class_compile common_methods_compile create_matrix_compile sequential_compile threads_compile process_compile main_compile matrex_exec clean_compiles

# matrix class
matrix_class_compile: modules/matrix_class.cpp
	g++ -Wall -c modules/matrix_class.cpp -fsanitize=address -g

# common_methods

common_methods_compile: modules/common_methods.cpp
	g++ -Wall -c modules/common_methods.cpp -fsanitize=address -g

# create_matrix

create_matrix_compile: modules/create_matrix.cpp
	g++ -Wall -c modules/create_matrix.cpp -fsanitize=address -g

# sequential

sequential_compile: modules/sequential.cpp
	g++ -Wall -c modules/sequential.cpp -fsanitize=address -g

# threads

threads_compile: modules/threads.cpp
	g++ -Wall -c modules/threads.cpp -fsanitize=address -g

# process

process_compile: modules/process.cpp
	g++ -Wall -c modules/process.cpp -fsanitize=address -g

# main

main_compile: main.cpp
	g++ -Wall -c main.cpp -fsanitize=address -g

matrex_exec:
	g++ matrix_class.o common_methods.o create_matrix.o sequential.o threads.o process.o main.o -o matrex_exec -fsanitize=address -static-libasan

clean_exec:
	rm -f matrex_exec

clean_compiles:
	rm -f matrix_class.o common_methods.o create_matrix.o sequential.o threads.o process.o main.o