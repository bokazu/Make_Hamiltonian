#include "all.h"

using namespace std;
// const size_t site = 4;  // size数を変えるごとに変更が必要

void smp(int i, int j, int site_num, int max_site_num, int dim,
         double *H)  // bra_iはsiteを変更するごとに手で変える必要あり
{
    boost::dynamic_bitset<> bra_i(max_site_num, i);
    boost::dynamic_bitset<> ket_j(max_site_num, j);
    boost::dynamic_bitset<> ket_j2(max_site_num, j);
    // bitset<site> bra_i(i);
    // bitset<site> ket_j(j);
    // bitset<site> ket_j2(j);
    bool bit_check0, bit_check1;

    if (site_num != max_site_num - 1)
    {
        bit_check0 = ket_j.test(site_num);
        bit_check1 = ket_j.test(site_num + 1);
    }
    else
    {
        bit_check0 = ket_j.test(site_num);
        bit_check1 = ket_j.test(0);
    }

    // Point A2
    if ((bit_check0 == true) && (bit_check1 == false))
    {
        // Point B2
        if (site_num != max_site_num - 1)
        {
            ket_j2.flip(site_num + 1);
            ket_j2.flip(site_num);
        }
        else
        {
            ket_j2.flip(0);
            ket_j2.flip(site_num);
        }

        // Point C2
        if (bra_i == ket_j2)
        {
            if (i == j)
                H[j + i * dim] += 0.5;
            else
            {
                H[j + i * dim] += 0.5;
                H[i + j * dim] += 0.5;
            }
        }
        else
        {
            if (i == j)
                H[j + i * dim] += 0.;
            else
            {
                H[j + i * dim] += 0.;
                H[i + j * dim] += 0.;
            }
        }
    }
    else
    {
        if (i == j)
            H[j + i * dim] += 0.;
        else
        {
            H[j + i * dim] += 0.;
            H[i + j * dim] += 0.;
        }
    }
}
