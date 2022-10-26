#include <iostream>

#include "DNS_Hamiltonian.h"

using namespace std;

int main()
{
    DNS_Hamiltonian H1("jset1.txt", 4);
    H1.init();
    cout << "H1の次元は" << H1.dim() << "です。"
         << "\n";
    DNS_Hamiltonian H2 = H1;


    // cout << "jset file : " << H1.jsetfile() << endl;
    // H1.print(1, 2);
}
