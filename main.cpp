#include "all.h"

using namespace std;
lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

int main()
{
    int max_site_num = 4;
    //<i|H|j>
    //|0> = |00>,|1> = |01>,|2> = |10>, |3> = |11> (|fermion2,fermion1>)
    string settingfile_name =
        "settingfile.txt";  //系のsite数、output用ファイル名の情報をこのfileに書いておく
    string OutputFile_name;  // output用file

    ifstream settingfile(settingfile_name);
    string ftmp;
    stringstream ss;
    int fcount = 0;
    while (!settingfile.eof())
    {
        getline(settingfile, ftmp);
        ss << ftmp;
        cout << "ftmp=" << ftmp << endl;
        if (fcount == 0)
        {
            ss >> max_site_num;
            cout << "max_site_num=" << max_site_num << endl;
        }
        else
        {
            OutputFile_name = ftmp;
            cout << "OutputFile_name = " << OutputFile_name << endl;
        }
        fcount += 1;
    }
    settingfile.close();

    int dim = 1 << max_site_num;
    string boundary;
    cout << "Impose Boundary Condition? y/n" << endl;
    cin >> boundary;
    cout << "dim=" << dim << endl;
    double *H = new double[dim * dim];
    double *lw = new double[dim];

    if (boundary == "y")
    {
        for (int site_num = 0; site_num < max_site_num; site_num++)
        {
            for (int i = 0; i < dim; i++)
            {
                for (int j = i; j < dim; j++)
                {
                    spm(i, j, site_num, max_site_num, dim, H);
                    smp(i, j, site_num, max_site_num, dim, H);
                    szz(i, j, site_num, max_site_num, dim, H);
                }
            }
        }
    }
    else if (boundary == "n")
    {
        for (int site_num = 0; site_num < max_site_num - 1; site_num++)
        {
            for (int i = 0; i < dim; i++)
            {
                for (int j = i; j < dim; j++)
                {
                    spm(i, j, site_num, max_site_num, dim, H);
                    smp(i, j, site_num, max_site_num, dim, H);
                    szz(i, j, site_num, max_site_num, dim, H);
                }
            }
        }
    }

    // /*OUTPUT HAMILTONIAN*/
    ofstream output(OutputFile_name);

    printmat(dim, H);
    fprintmat(output, dim, H);

    // // Check My Code by LAPACK
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'U', dim, H, dim, lw);

    output << "LAPACKE's Eigen value" << endl;
    fprintvec(output, dim, lw);
    output << "\n LAPACKE's Eigen vector" << endl;
    fprintmat(output, dim, H);
    delete[] H;
}
