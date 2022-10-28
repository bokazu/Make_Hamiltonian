#include <iostream>

#include "DNS_Hamiltonian.h"
#include "Jset.h"

using namespace std;

int main()
{
    DNS_Hamiltonian H1("jset1.txt", 2);

    H1.init();

    cout << "H1の次元は" << H1.dim() << "です。"
         << "\n";

    H1.jset();

    std::cout << " tot_site_num = " << H1.site() << std::endl;

    H1.hamiltonian();

    H1.print(0, 0);
    H1.print(1, 1);
    H1.print(1, 2);
    H1.print(2, 1);
    H1.print(2, 2);
    H1.print(3, 3);
}
