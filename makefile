gcc_options = -std=c++17 -Wall --pedantic-errors -DMKL_ILP64  -I"${MKLROOT}/include" -g
l_b = -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -liomp5 -lpthread -lm -ldl

program : HamiltonianTest.o Hamiltonian.o
	g++ -o $@ $^ $(l_b)

HamiltonianTest.o : HamiltonianTest.cpp
	g++ -c $@ $< $(l_b)

Hamiltonian.o : Hamiltonian.cpp
	g++ -c $@ $< $(l_b)

# program : main.o hamiltonian.o spin.o jset.o print_matrix.o
# 	g++ -o $@ $^

# main.o : main.cpp
# 	g++ -c $< 

# hamiltonian.o : hamiltonian.cpp
# 	g++ -c $< 

# spin.o : spin.cpp
# 	g++ -c $< 

# jset.o : jset.cpp
# 	g++ -c $<

# print_matrix.o : print_matrix.cpp
# 	g++ -c $< 

run : program
	./program

clean:
	rm -f ./program

.PHONY : run clean
