#include "all.h"

using namespace std;
lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

int main()
{
    int tot_site_num;
    //<i|H|j>
    //|0> = |00>,|1> = |01>,|2> = |10>, |3> = |11> (|fermion2,fermion1>)
    string settingfile_name =
        "model_set/settingfile.txt";  //系のsite数、output用ファイル名の情報をこのfileに書いておく
    string OutputFile_name;           // output用file

    ifstream settingfile(settingfile_name);
    string ftmp, Boundary_Condition;
    stringstream ss;
    int fcount = 0;
    while (!settingfile.eof())
    {
        getline(settingfile, ftmp);
        ss << ftmp;
        cout << "ftmp=" << ftmp << endl;
        if (fcount == 0)
        {
            ss >> tot_site_num;
            cout << "tot_site_num=" << tot_site_num << endl;
        }
        else if (fcount == 1)
        {
            OutputFile_name = ftmp;
            cout << "OutputFile_name = " << OutputFile_name << endl;
        }
        else if (fcount == 2)
        {
            Boundary_Condition = ftmp;
            cout << "Boundary Condition : " << Boundary_Condition << endl;
        }
        fcount += 1;
    }
    settingfile.close();

    int dim = 1 << tot_site_num;
    string boundary;
    cout << "dim=" << dim << endl;
    double *H = new double[dim * dim];
    double *lw = new double[dim];

    // Hamiltonianの初期化(全要素0で埋める)
    for (int i = 0; i < dim * dim; i++) H[i] = 0.;

    if (Boundary_Condition == "y")
    {
        for (int site_num = 0; site_num < tot_site_num; site_num++)
        {
            for (int j = 0; j < dim; j++)
            {
                spm(j, site_num, tot_site_num, dim, H);
                smp(j, site_num, tot_site_num, dim, H);
                szz(j, site_num, tot_site_num, dim, H);
            }
        }
    }
    else if (Boundary_Condition == "n")
    {
        for (int site_num = 0; site_num < tot_site_num - 1; site_num++)
        {
            for (int j = 0; j < dim; j++)
            {
                spm(j, site_num, tot_site_num, dim, H);
                smp(j, site_num, tot_site_num, dim, H);
                szz(j, site_num, tot_site_num, dim, H);
            }
        }
    }

    // /*OUTPUT HAMILTONIAN*/
    ofstream output(OutputFile_name);
    output << "Total Site Num = " << tot_site_num << endl;
    output << "Boundary Condition : " << Boundary_Condition << endl;

    printmat(dim, H);
    fprintmat(output, dim, H);

    // // Check My Code by LAPACK
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'U', dim, H, dim, lw);

    output << "LAPACKE's Eigen value" << endl;
    fprintvec(output, dim, lw);
    output << "\n LAPACKE's Eigen vector" << endl;
    fprintmat(output, dim, H);

    output.close();
    delete[] H;
}
