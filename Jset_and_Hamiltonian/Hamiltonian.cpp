#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "DNS_Hamiltonian.h"
#include "Jset.h"
#include "cblas.h"

using namespace std;

//コピーコンストラクタ
DNS_Hamiltonian::DNS_Hamiltonian(const DNS_Hamiltonian& h) : jset_filename(h.jset_filename), tot_site_num(h.tot_site_num), mat_dim(h.mat_dim), J(h.J)
{
    H = new double[mat_dim * mat_dim];
    cblas_dcopy(mat_dim * mat_dim, h.H, 1, H, 1);
    std::cout << "copy has done.\n";
}

//代入演算子
DNS_Hamiltonian& DNS_Hamiltonian::operator=(const DNS_Hamiltonian& h) { cblas_dcopy(mat_dim * mat_dim, h.H, 1, H, 1); }

//行列の初期化
void DNS_Hamiltonian::init()
{
    for (int i = 0; i < mat_dim; i++) H[i] = 0.0;
}

// Hamiltonianの第[i][j]要素を標準出力する
void DNS_Hamiltonian::print(int i, int j) const
{
    cout << "H[" << i << "]"
         << "[" << j << "] = " << H[i + j * mat_dim] << "\n";
}

//ハミルトニアン行列を求める
void DNS_Hamiltonian::hamiltonian()
{
    std::cout << "hamiltonian()\n";
    std::cout << "J.index(0,1)" << J.index(0, 1) << std::endl;
    for (int m = 0; m < mat_dim; m++)
    {
        for (int site_i = 0; site_i < tot_site_num; site_i++)
        {
            std::cout << "(m,site_i) = (" << m << " , " << site_i << ")\n";
            spin(m, site_i);
        }
    }
}

//スピン演算子と状態ベクトルの計算を行う
void DNS_Hamiltonian::spin(int m, int site_i)
{
    boost::dynamic_bitset<> ket_m(tot_site_num, m);  // LH->1N_4
    bool bit_check0, bit_check1;
    int j_line = 0;
    for (int l = j_line; l < J.get_line(); l++)
    {
        if (J.index(0, l) == site_i)
        {
            int site_j = J.index(1, l);
            cout << "(site_i,site_j )= (" << site_i << "," << site_j << ")\n";
            bit_check0 = ket_m.test(site_i);  // LH->1N->2Y_1
            bit_check1 = ket_m.test(site_j);  // LH->1N->2Y_1

            // LH->1N->3 (注目している2サイトについての場合分け)
            if (bit_check0 == bit_check1)
            {
                // S^z_{i}S^z_{i+1}|1_{i+1} 1_{i}> or S^z_{i}S^z_{i+1}|0_{i+1} 0_{i}>
                H[m + m * mat_dim] += 0.25 * J.val(l);
                std::cout << "H[" << m << "][" << m << "] = " << at(m, m) << endl;
                std::cout << "J.val(" << l << ") = " << J.val(l) << endl;
            }
            else
            {
                boost::dynamic_bitset<> ket_m1(tot_site_num, m);  // LH->1N_4
                // LH->1N->3Y->1
                ket_m1.flip(site_j);        // LH->1N->3Y->1Y_1
                ket_m1.flip(site_i);        // LH->1N->3Y->1Y_1
                int n = ket_m1.to_ulong();  // LH->1N->3N_1

                std::cout << "J.val(" << l << ") = " << J.val(l) << endl;
                // S^-_{i}S^+_{i+1} or S^+_{i}S^-_{i+1}
                H[m + n * mat_dim] += 0.5 * J.val(l);
                std::cout << "H[" << n << "][" << m << "] = " << at(n, m) << endl;
                // S^z_{i}S^z_{i+1}|0_{i+1} 1_{i}>
                H[m + m * mat_dim] -= 0.25 * J.val(l);
                std::cout << "H[" << m << "][" << m << "] = " << at(m, m) << endl;
            }
            j_line++;
        }
    }
}
