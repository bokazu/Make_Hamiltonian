#include "all.h"

using namespace std;

void spin_operator(int m, int site_i, const int mat_dim, const int tot_site_num, double* H)
{
    boost::dynamic_bitset<> ket_m(tot_site_num, m);  // LH->1N_4
    bool bit_check0, bit_check1;
    int jset_line = 0;
    for (int l = jset_line; l < Jset_line; l++)
    {
        if (J_index[l][0] == site_i)
        {
            int site_j = J_index[l][1];
            // cout << "(site_i,site_j )= (" << site_i << "," << site_j <<
            // ")\n";
            bit_check0 = ket_m.test(site_i);  // LH->1N->2Y_1
            bit_check1 = ket_m.test(site_j);  // LH->1N->2Y_1

            // LH->1N->3 (注目している2サイトについての場合分け)
            if (bit_check0 == bit_check1)
            {
                // S^z_{i}S^z_{i+1}|1_{i+1} 1_{i}> or S^z_{i}S^z_{i+1}|0_{i+1} 0_{i}>
                H[m + m * mat_dim] += 0.25 * J_val[l];
            }
            else
            {
                boost::dynamic_bitset<> ket_m1(tot_site_num, m);  // LH->1N_4
                // LH->1N->3Y->1
                ket_m1.flip(site_j);        // LH->1N->3Y->1Y_1
                ket_m1.flip(site_i);        // LH->1N->3Y->1Y_1
                int n = ket_m1.to_ulong();  // LH->1N->3N_1

                // S^-_{i}S^+_{i+1} or S^+_{i}S^-_{i+1}
                H[n + m * mat_dim] += 0.5 * J_val[l];

                /*********行列要素が正しく求まっているかを確認する用*************/
                // cout << "mat_val[" << n << "][" << m << "] = " << mat_val <<
                // endl;
                /****************************************************************/
                // S^z_{i}S^z_{i+1}|0_{i+1} 1_{i}>
                H[m + m * mat_dim] -= 0.25 * J_val[l];
            }
            jset_line++;
        }
    }
}

int nnz_counter(const int mat_dim, const int tot_site_num)
{
    int nnz = 0;
    double szz = 0.;
    for (int m = 0; m < mat_dim; m++)
    {
        for (int site_i = 0; site_i < tot_site_num; site_i++)
        {
            boost::dynamic_bitset<> ket_m(tot_site_num, m);  // LH->1N_4
            bool bit_check0, bit_check1;
            int jset_line = 0;
            for (int l = jset_line; l < Jset_line; l++)
            {
                szz = 0.;
                if (J_index[l][0] == site_i)
                {
                    int site_j = J_index[l][1];
                    // cout << "(site_i,site_j )= (" << site_i << "," << site_j <<
                    // ")\n";
                    bit_check0 = ket_m.test(site_i);  // LH->1N->2Y_1
                    bit_check1 = ket_m.test(site_j);  // LH->1N->2Y_1

                    // LH->1N->3 (注目している2サイトについての場合分け)
                    if (bit_check0 == bit_check1)
                    {
                        // S^z_{i}S^z_{i+1}|1_{i+1} 1_{i}> or S^z_{i}S^z_{i+1}|0_{i+1} 0_{i}>
                        szz += 0.25 * J_val[l];
                    }
                    else
                    {
                        boost::dynamic_bitset<> ket_m1(tot_site_num, m);  // LH->1N_4
                        // LH->1N->3Y->1
                        ket_m1.flip(site_j);        // LH->1N->3Y->1Y_1
                        ket_m1.flip(site_i);        // LH->1N->3Y->1Y_1
                        int n = ket_m1.to_ulong();  // LH->1N->3N_1

                        // S^-_{i}S^+_{i+1} or S^+_{i}S^-_{i+1}
                        nnz++;

                        /*********行列要素が正しく求まっているかを確認する用*************/
                        // cout << "mat_val[" << n << "][" << m << "] = " << mat_val <<
                        // endl;
                        /****************************************************************/
                        // S^z_{i}S^z_{i+1}|0_{i+1} 1_{i}>
                        szz -= 0.25 * J_val[l];
                    }
                    jset_line++;
                }
            }
        }
        if (szz != 0.0) nnz++;
    }

    return nnz;
}

void COO_spin_operator(int m, int site_i, const int mat_dim, const int tot_site_num, double& szz, int& coo_index, int* row, int* col, double* val)
{
    boost::dynamic_bitset<> ket_m(tot_site_num, m);  // LH->1N_4
    bool bit_check0, bit_check1;
    int jset_line = 0;
    for (int l = jset_line; l < Jset_line; l++)
    {
        if (J_index[l][0] == site_i)
        {
            int site_j = J_index[l][1];
            // cout << "(site_i,site_j )= (" << site_i << "," << site_j <<
            // ")\n";
            bit_check0 = ket_m.test(site_i);  // LH->1N->2Y_1
            bit_check1 = ket_m.test(site_j);  // LH->1N->2Y_1

            // LH->1N->3 (注目している2サイトについての場合分け)
            if (bit_check0 == bit_check1)
            {
                // S^z_{i}S^z_{i+1}|1_{i+1} 1_{i}> or S^z_{i}S^z_{i+1}|0_{i+1} 0_{i}>
                szz += 0.25 * J_val[l];
            }
            else
            {
                boost::dynamic_bitset<> ket_m1(tot_site_num, m);  // LH->1N_4
                // LH->1N->3Y->1
                ket_m1.flip(site_j);        // LH->1N->3Y->1Y_1
                ket_m1.flip(site_i);        // LH->1N->3Y->1Y_1
                int n = ket_m1.to_ulong();  // LH->1N->3N_1

                // S^-_{i}S^+_{i+1} or S^+_{i}S^-_{i+1}
                row[coo_index] = n;
                col[coo_index] = m;
                val[coo_index] += 0.5 * J_val[l];
                coo_index++;

                /*********行列要素が正しく求まっているかを確認する用*************/
                // cout << "mat_val[" << n << "][" << m << "] = " << mat_val <<
                // endl;
                /****************************************************************/
                // S^z_{i}S^z_{i+1}|0_{i+1} 1_{i}>
                szz -= 0.25 * J_val[l];
            }
            jset_line++;
        }
    }
}

void CSC_spin_operator(int m, int site_i, const int tot_site_num, int* row, int& row_index, double* val, int& cptr_val, double& szz)
{
    boost::dynamic_bitset<> ket_m(tot_site_num, m);  // LH->1N_4
    bool bit_check0, bit_check1;
    int jset_line = 0;
    for (int l = jset_line; l < Jset_line; l++)
    {
        if (J_index[l][0] == site_i)
        {
            int site_j = J_index[l][1];
            // cout << "(site_i,site_j )= (" << site_i << "," << site_j <<
            // ")\n";
            bit_check0 = ket_m.test(site_i);  // LH->1N->2Y_1
            bit_check1 = ket_m.test(site_j);  // LH->1N->2Y_1

            // LH->1N->3 (注目している2サイトについての場合分け)
            if (bit_check0 == bit_check1)
            {
                // S^z_{i}S^z_{i+1}|1_{i+1} 1_{i}> or S^z_{i}S^z_{i+1}|0_{i+1} 0_{i}>
                szz += 0.25 * J_val[l];
            }
            else
            {
                boost::dynamic_bitset<> ket_m1(tot_site_num, m);  // LH->1N_4
                // LH->1N->3Y->1
                ket_m1.flip(site_j);        // LH->1N->3Y->1Y_1
                ket_m1.flip(site_i);        // LH->1N->3Y->1Y_1
                int n = ket_m1.to_ulong();  // LH->1N->3N_1

                // S^-_{i}S^+_{i+1} or S^+_{i}S^-_{i+1}
                row[row_index] = n;
                val[row_index] += 0.5 * J_val[l];
                row_index++;
                cptr_val++;

                /*********行列要素が正しく求まっているかを確認する用*************/
                // cout << "mat_val[" << n << "][" << m << "] = " << mat_val <<
                // endl;
                /****************************************************************/
                // S^z_{i}S^z_{i+1}|0_{i+1} 1_{i}>
                szz -= 0.25 * J_val[l];
            }
            jset_line++;
        }
    }
}