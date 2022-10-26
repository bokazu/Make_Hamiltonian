#ifndef ___Class_Jset
#define ___Class_Jset

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

class Jset{
    private:
      std::string jset_filename;
      int jset_line;
      int** J_index;
      double* J_val;
      
    public:
    //コンストラクタ
    Jset(std::string filename) : jset_filename(filename) {
        jset_line = lines();
        std::cout << "jset_line = " << jset_line << "\n";
        J_index = new int*[2];
        for(int i = 0; i < 2; i++) J_index[i] = new int[jset_line];
        J_val = new double[jset_line];
        std::cout << "Jset is constructed.\n";
    }

    //コピーコンストラクタ
    Jset(const Jset& x);

    //デストラクタ
    ~Jset(){
        for(int i = 0; i < 2;i++){
            delete[] J_index[i];
        }
        delete[] J_index;
        delete[] J_val;
        std::cout << "Jset is destructed.\n";
    }

    //ムーブコンストラクタ
    // Jset(const Jset&& x) noexcept : jset_filename(x.jset_filename), jset_line(x.jset_line),J_index(x.J_index), J_val(x.J_val){
    // }

    //---代入演算子=----//
    Jset& operator=(const Jset& x);

    //jset用のファイルが存在するかを調べる
    static bool file_check(std::string filename);
    
    //Jsetの情報を標準出力する
    void print() const;
    
    //jsetの情報を配列に代入する
    void set();

    int index(int i,int j){return J_index[i][j];}
    int val(int i){return J_val[i];}
    int lines();
};

#endif