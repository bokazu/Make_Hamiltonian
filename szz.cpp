#include "all.h"

using namespace std;
// const size_t site = 4;

void szz(int i, int j, int site_num, int max_site_num, int dim,
         double *H)  // bra_iはsiteを変更するごとに手で変える必要あり
{
    int n;
    boost::dynamic_bitset<> bra_i(max_site_num, i);
    boost::dynamic_bitset<> ket_j(max_site_num, j);
    // bitset<site> bra_i(i);
    // bitset<site> ket_j(j);
    bool bit_check0, bit_check1;
    // if (site_num != max_site_num - 1)
    // {
    //     bit_check0 = ket_j.test(site_num);
    //     bit_check1 = ket_j.test(site_num + 1);
    // }
    // else
    // {
    //     bool bit_check0 = ket_j.test(site_num);
    //     bool bit_check1 = ket_j.test(0);
    // }

    if (site_num == max_site_num - 1)
    {
        bit_check0 = ket_j.test(site_num);
        bit_check1 = ket_j.test(0);
    }
    else
    {
        bit_check0 = ket_j.test(site_num);
        bit_check1 = ket_j.test(site_num + 1);
    }

    // Point A3
    if (bra_i != ket_j)
    {
        if (i == j)
            H[j + i * dim] += 0.;
        else
        {
            H[j + i * dim] += 0.;
            H[i + j * dim] += 0.;
        }
    }
    else
    {
        if (bit_check0 == bit_check1)
        {
            if (i == j)
                H[j + i * dim] += 0.25;
            else
            {
                H[j + i * dim] += 0.25;
                H[i + j * dim] += 0.25;
            }
        }
        else
        {
            if (i == j)
                H[j + i * dim] -= 0.25;
            else
            {
                H[j + i * dim] -= 0.25;
                H[i + j * dim] -= 0.25;
            }
        }
    }
}