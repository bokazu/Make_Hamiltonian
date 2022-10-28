#include "all.h"

using namespace std;

int Jset_line;

int main()
{
    //==============モデルによって変更する箇所======================//
    const int tot_site_num = 4;
    string jset_filename = "jset/jset_4site.txt";
    //==============================================================//

    cout << "=======================================================================\n"
         << "INPUT FILE : " << jset_filename << endl
         << "=======================================================================\n";

    hamiltonian('1', 'y', tot_site_num, jset_filename);

    for (int i = 0; i < 2; i++)
    {
        delete[] J_index[i];
    }
    delete[] J_index;
    delete[] J_val;
}
