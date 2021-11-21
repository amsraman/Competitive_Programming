#include <iostream>

using namespace std;

int l, w;
string a = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    cin >> l >> w;
    if((w<l)||(w>l*26))
    {
        cout << "impossible" << endl;
    }
    else
    {
        for(int i = 0; i<l-(w%l); i++) cout << a[(w/l)-1];
        for(int i = 0; i<w%l; i++) cout << a[(w/l)];
        cout << endl;
    }
}
