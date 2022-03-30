gcc_options = -std=c++17 -Wall --pedantic-errors -g
l_b = -llapacke -lblas -lcblas

program : main.o spm.o smp.o szz.o print_matrix.o
	g++ -o $@ $^ $(l_b)

main.o : main.cpp
	g++ -c $< $(l_b)

spm.o : spm.cpp
	g++ -c $< $(l_b)

smp.o : smp.cpp
	g++ -c $< $(l_b)

szz.o : szz.cpp
	g++ -c $< $(l_b)

print_matrix.o : print_matrix.cpp
	g++ -c $< $(l_b)

run : program
	./program

clean:
	rm -f ./program

.PHONY : run clean