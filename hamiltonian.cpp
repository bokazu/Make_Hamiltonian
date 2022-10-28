#include "all.h"

using namespace std;

int hamiltonian(char f, char info_jset, const int tot_site_num, string jset_filename)
{
    const int mat_dim = 1 << tot_site_num;

    cout << "=======================================================================\n"
         << "INPUT FILE : " << jset_filename << endl
         << "=======================================================================\n";
    int info_j = 0;
    Jset_line = 0;
    info_jset = jset(jset_filename);  //条件に合うファイルが存在しなければ-1を返す
    if (info_j == 0)
    {
        if (f == '1')  // DNS FORMAT
        {
            double* H = new double[mat_dim * mat_dim];
            vec_init(mat_dim * mat_dim, H);
            hamiltonian_dns(tot_site_num, mat_dim, H);

            printmat(mat_dim, H);
            delete[] H;
        }
        else if (f == '2')  // COO FORMAT
        {
            int nnz = 0;
            double szz = 0.;

            for (int m = 0; m < mat_dim; m++)
            {
                szz = 0.;
                nnz = nnz_counter(mat_dim, tot_site_num);

                int* row = new int[nnz];
                int* col = new int[nnz];
                double* val = new double[nnz];

                vec_init(nnz, row);
                vec_init(nnz, col);
                vec_init(nnz, val);

                hamiltonian_coo(tot_site_num, mat_dim, row, col, val);

                delete[] row;
                delete[] col;
                delete[] val;
            }
        }
        else if (f == '3')  // CSC FORMAT
        {
            int nnz = 0;
            double szz = 0.;

            nnz = nnz_counter(mat_dim, tot_site_num);

            int* row = new int[nnz];
            int* cptr = new int[mat_dim + 1];
            double* val = new double[nnz];

            vec_init(nnz, row);
            vec_init(mat_dim + 1, cptr);
            vec_init(nnz, val);

            delete[] row;
            delete[] cptr;
            delete[] val;
        }
    }
    return info_j;
}

// DNS形式で行列を確保する
// J_indexとJ_valはextern宣言しているので引数には取らない
int hamiltonian_dns(const int tot_site_num, const int mat_dim, double* H)
{
    cout << "Calculate Hamiltonian elements with COO format\n";

    //====================行列要素の計算====================//
    for (int m = 0; m < mat_dim; m++)
    {
        for (int site_i = 0; site_i < tot_site_num; site_i++)
        {
            spin_operator(m, site_i, mat_dim, tot_site_num, H);
        }
    }
    return 0;
}

// COO形式で行列を確保する
int hamiltonian_coo(const int tot_site_num, const int mat_dim, int* row, int* col, double* val)
{
    double szz = 0.;
    //======================COO形式での行列要素の計算========================//
    int coo_index = 0;
    for (int m = 0; m < mat_dim; m++)
    {
        szz = 0.;
        for (int site_i = 0; site_i < tot_site_num; site_i++)
        {
            COO_spin_operator(m, site_i, mat_dim, tot_site_num, szz, coo_index, row, col, val);
        }
        if (szz != 0.)
        {
            row[coo_index] = m;
            col[coo_index] = m;
            val[coo_index] = szz;
            coo_index++;
        }
    }
    return 0;
}

int hamiltonian_csc(const int tot_site_num, const int mat_dim, int* row, int* cptr, double* val, const int& nnz)
{
    int row_index = 0;
    int cptr_index = 0;
    int cptr_val = 0;
    double szz = 0.;

    for (int m = 0; m < mat_dim; m++)
    {
        szz = 0.;

        cptr[cptr_index] = cptr_val;
        cptr_index++;

        for (int site_i = 0; site_i < tot_site_num; site_i++)
        {
            CSC_spin_operator(m, site_i, tot_site_num, row, row_index, val, cptr_val, szz);
        }
        if (szz != 0.)
        {
            val[row_index] = szz;
            row[row_index] = m;
            row_index++;
            cptr_val++;
        }
    }
    return 0;
}