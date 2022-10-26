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
DNS_Hamiltonian::DNS_Hamiltonian(const DNS_Hamiltonian& h) : jset_filename(h.jset_filename),tot_site_num(h.tot_site_num),mat_dim(h.mat_dim),J(h.J)
{
    H = new double[mat_dim*mat_dim];
    cblas_dcopy(mat_dim * mat_dim, h.H, 1, H, 1);
    std::cout << "copy has done.\n";
}

//代入演算子
DNS_Hamiltonian& DNS_Hamiltonian::operator=(const DNS_Hamiltonian& h){
    cblas_dcopy(mat_dim * mat_dim, h.H, 1, H, 1);
}

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
//スピン演算子と状態ベクトルの計算を行う
void spin_operator(int m, int site_i, DNS_Hamiltonian H) {}

// Hamiltonianの行列要素を計算する
//  void DNS_Hamiltonian::hamiltonian(){
//      for(int m = 0; m < mat_dim; m++){
//          for(int site_i = 0; site_i < tot_site_num;site_i++){

//         }
//     }
// }
