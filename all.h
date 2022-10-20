#ifndef __MYlIB_H_
#define __MYlIB_H_

#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

extern int Jset_line;
extern int** J_index;
extern double* J_val;

int jset(std::string jset_filename);

//===================================spin.cpp===============================//
void spin_operator(int m, int site_i, const int mat_dim, const int tot_site_num, double* H);
int nnz_counter(const int mat_dim, const int tot_site_num);  // COO、CSCで使用する
void COO_spin_operator(int m, int site_i, const int mat_dim, const int tot_site_num, double& szz, int& coo_index, int* row, int* col, double* val);
void CSC_spin_operator(int m, int site_i, const int tot_site_num, int* row, int& row_index, double* val, int& cptr_val, double& szz);

//=================================hamiltonian.cpp===========================//
int hamiltonian(char f, char info_jset, const int tot_site_num, std::string jset_filename);
//--------------------------------for DNS FORMAT-----------------------------//
int hamiltonian_dns(const int tot_site_num, const int mat_dim, double* H);
//--------------------------------for COO FORMAT-----------------------------//
int hamiltonian_coo(const int tot_site_num, const int mat_dim, int* row, int* col, double* val);
//--------------------------------for CSC FORMAT------------------------------//

//==============================================================================//
void printmat(int n, double* A);
void fprintmat(std::ofstream& file, int n, double* A);
void printvec(int n, double* B);
void fprintvec(std::ofstream& file, int n, double* B);
void print2dvec(int n, double** C);
void fprint2dvec(std::ofstream& file, int n, double** C);

template <typename T>
void vec_init(int n, T* vec)
{
    for (int i = 0; i < n; i++)
    {
        vec[i] = 0;
    }
}

#endif