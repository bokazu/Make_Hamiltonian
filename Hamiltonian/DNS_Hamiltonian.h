#ifndef ___Class_Hamiltonian
#define ___Class_Hamiltonian

#include <iomanip>

class DNS_Hamiltonian
{
  private:
    std::string jset_filename;
    int tot_site_num;
    int mat_dim;
    double* H;


  
  public:
    //明示的コンストラクタ
    explicit DNS_Hamiltonian(std::string filename, int site) : jset_filename(filename), tot_site_num(site), mat_dim(1 << tot_site_num)
    {
        //配列を動的確保し、0で初期化する
        H = new double[mat_dim * mat_dim];
        for (int i = 0; i < mat_dim * mat_dim; i++)
        {
            H[i] = 0.0;
        }
        std::cout << "DNS_Hamiltonian::constructed.\n";
    }

    //コピーコンストラクタ
    DNS_Hamiltonian(const DNS_Hamiltonian& h);
    //デストラクタ
    ~DNS_Hamiltonian()
    {
        delete[] H;
        std::cout << "DNS_Hamiltonian::destructed.\n";
    }

    // Hamiltonian行列の先頭要素へのポインタを返す
    double* data() { return H; }
    //系のサイト数を返す
    int site() const { return tot_site_num; }
    //行列の次元を返す
    int dim() const { return mat_dim; }
    // jsetの情報を書き込んだファイルの名前を返す
    std::string jsetfile() const { return jset_filename; }

    //代入演算子=
    DNS_Hamiltonian& operator=(const DNS_Hamiltonian& h);
    //添字演算子[]
    double& operator[](int i) { return H[i]; }
    // const版添字演算子
    const double& operator[](int i) const { return H[i]; }

    // Hamiltonianを0で初期化
    void init();
    // Hamiltonianの行列要素を計算する
    void hamiltonian();


    // Hamiltonianの第[i][j]要素を標準出力する
    void print(int i, int j) const;
};

#endif
