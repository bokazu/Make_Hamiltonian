gcc_options = -std=c++17 -Wall --pedantic-errors -DMKL_ILP64  -I"${MKLROOT}/include" -g
l_b = -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -liomp5 -lpthread -lm -ldl

program : HamiltonianTest.o Hamiltonian.o Jset.o
	g++ -o $@ $^ $(l_b)

HamiltonianTest.o : HamiltonianTest.cpp
	g++ -c $< $(l_b)

Hamiltonian.o : Hamiltonian.cpp
	g++ -c $< $(l_b)

Jset.o : Jset.cpp
	g++ -c $< $(l_b)
	
run : program
	./program

clean:
	rm -f ./program

.PHONY : run clean
