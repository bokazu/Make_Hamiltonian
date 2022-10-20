#include "all.h"

using namespace std;

int** J_index;
double* J_val;

int jset(string jset_filename)
{
    ifstream if_jset(jset_filename);
    if (!(if_jset))
    {
        cerr << "Could not open the file - '" << jset_filename << "'" << endl;
        return -1;
    }
    else
    {
        string count_tmp;
        while (getline(if_jset, count_tmp))  //ファイル行数のカウント
        {
            Jset_line++;
        }

        J_index = new int*[Jset_line];
        J_val = new double[Jset_line];

        for (int k = 0; k < Jset_line; k++)
        {
            J_index[k] = new int[2];
        }

        string str_tmp;
        int J_ind_temp_i, J_ind_temp_j;
        double J_val_temp;

        for (int k = 0; k < Jset_line; k++)
        {
            J_index[k][0] = 0;
            J_index[k][1] = 0;
            J_val[k] = 0.;
        }

        int line = 0;

        //ファイルの読みとりスタート箇所を先頭に戻す
        if_jset.clear();
        if_jset.seekg(std::ios::beg);
        while (getline(if_jset, str_tmp))
        {
            stringstream ss;
            ss << str_tmp;
            ss >> J_ind_temp_i >> J_ind_temp_j >> J_val_temp;
            J_index[line][0] = J_ind_temp_i;
            J_index[line][1] = J_ind_temp_j;
            J_val[line] = J_val_temp;
            line++;
        }
        return 0;
    }
}