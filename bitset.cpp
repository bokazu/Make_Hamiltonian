/*dynamic_bitsetのテスト用のfile。make_hamiltonianには必要ないので最後に削除するのを忘れない*/

#include "all.h"

using namespace std;

int main()
{
    boost::dynamic_bitset<> dbs(4, 3);
    bitset<4> bs(3);

    // test(),[] 特定のビットが1かどうかを調べる
    bool dcheck, check;
    dcheck = dbs.test(0);
    check = bs.test(0);
    cout << "dcheck(by test(),at 0) = " << dcheck << endl;
    cout << "check(at,0) = " << check << endl;

    dcheck = dbs[3];
    cout << "dcheck(by [],at 3) = " << dcheck << endl;
    dcheck = dbs[0];
    cout << "dcheck(by [],at 0) = " << dcheck << endl;

    // flip()の確認
    dbs.flip(0);
    cout << "dbs(flip(0)) = " << dbs << endl;
    dbs.flip(3);
    cout << "dbs(flip(3)) = " << dbs << endl;
    dbs.flip();
    cout << "dbs(flip()) = " << dbs << endl;
}