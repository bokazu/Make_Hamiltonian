#include "all.h"

using namespace std;
// const size_t site = 4;

void szz(int j, int site_num, int tot_site_num, int dim,
         double *H)  // bra_iはsiteを変更するごとに手で変える必要あり
{
    int J = 1;

    // Point A2
    boost::dynamic_bitset<> ket_j(tot_site_num, j);
    bool bit_check0, bit_check1;

    // Point B2
    if (site_num == tot_site_num - 1)
    {
        bit_check0 = ket_j.test(site_num);
        bit_check1 = ket_j.test(0);
    }
    else
    {
        bit_check0 = ket_j.test(site_num);
        bit_check1 = ket_j.test(site_num + 1);
    }

    // Hamiltonianへの代入
    if (bit_check0 == bit_check1)
    {
        H[j + j * dim] += 0.25 * J;
    }
    else
    {
        H[j + j * dim] -= 0.25 * J;
    }
}