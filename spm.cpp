#include "all.h"

using namespace std;
// const size_t site = 4;  // size数を変えるごとに変更が必要

void spm(int i, int j, int site_num, int max_site_num, int dim,
         double *H)  // bra_iはsiteを変更するごとに手で変える必要あり
{
    boost::dynamic_bitset<> bra_i(max_site_num, i);
    boost::dynamic_bitset<> ket_j(max_site_num, j);
    boost::dynamic_bitset<> ket_j1(max_site_num, j);
    // bitset<site> bra_i(i);
    // bitset<site> ket_j(j);
    // bitset<site> ket_j1(j);
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

    // Point A
    if ((bit_check0 == false) && (bit_check1 == true))
    {
        // Point B
        if (site_num != max_site_num - 1)
        {
            ket_j1.flip(site_num + 1);
            ket_j1.flip(site_num);
        }
        else
        {
            ket_j1.flip(0);
            ket_j1.flip(site_num);
        }

        // Point C
        if (bra_i == ket_j1)
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

// void smp(int i, int j, int site_num, int dim,
//          double *H)  // bra_iはsiteを変更するごとに手で変える必要あり
// {
//     bitset<site> bra_i(i);
//     bitset<site> ket_j(j);
//     bitset<site> ket_j2(j);

//     bool bit_check0 = ket_j.test(site_num);
//     bool bit_check1 = ket_j.test(site_num + 1);

//     // Point A2
//     if ((bit_check0 == true) && (bit_check1 == false))
//     {
//         // Point B2
//         ket_j2.set(site_num + 1, 1);
//         ket_j2.set(site_num, 0);
//         // Point C2
//         if (bra_i == ket_j2)
//         {
//             if (i == j)
//                 H[j + i * dim] += 0.5;
//             else
//             {
//                 H[j + i * dim] += 0.5;
//                 H[i + j * dim] += 0.5;
//             }
//         }
//         else
//         {
//             if (i == j)
//                 H[j + i * dim] += 0.;
//             else
//             {
//                 H[j + i * dim] += 0.;
//                 H[i + j * dim] += 0.;
//             }
//         }
//     }
//     else
//     {
//         if (i == j)
//             H[j + i * dim] += 0.;
//         else
//         {
//             H[j + i * dim] += 0.;
//             H[i + j * dim] += 0.;
//         }
//     }
// }

// void szz(int i, int j, int site_num, int dim,
//          double *H)  // bra_iはsiteを変更するごとに手で変える必要あり
// {
//     bitset<site> bra_i(i);
//     bitset<site> ket_j(j);
//     bool bit_check0 = ket_j.test(site_num);
//     bool bit_check1 = ket_j.test(site_num + 1);
//     // Point A3
//     if (bra_i != ket_j)
//     {
//         if (i == j)
//             H[j + i * dim] += 0.;
//         else
//         {
//             H[j + i * dim] += 0.;
//             H[i + j * dim] += 0.;
//         }
//     }
//     else
//     {
//         if (bit_check0 == bit_check1)
//         {
//             if (i == j)
//                 H[j + i * dim] += 0.25;
//             else
//             {
//                 H[j + i * dim] += 0.25;
//                 H[i + j * dim] += 0.25;
//             }
//         }
//         else
//         {
//             if (i == j)
//                 H[j + i * dim] += -0.25;
//             else
//             {
//                 H[j + i * dim] += -0.25;
//                 H[i + j * dim] += -0.25;
//             }
//         }
//     }
// }