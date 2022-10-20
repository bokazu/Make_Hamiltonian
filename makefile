gcc_options = -std=c++17 -Wall --pedantic-errors -g

program : main.o hamiltonian.o spin.o jset.o print_matrix.o
	g++ -o $@ $^

main.o : main.cpp
	g++ -c $< 

hamiltonian.o : hamiltonian.cpp
	g++ -c $< 

spin.o : spin.cpp
	g++ -c $< 

jset.o : jset.cpp
	g++ -c $<

print_matrix.o : print_matrix.cpp
	g++ -c $< 

run : program
	./program

clean:
	rm -f ./program

.PHONY : run clean