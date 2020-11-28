#include <iostream>

using namespace std;

int t, n;

int main()
{
    cin >> t;
    for(int z = 0; z<t; z++)
    {
        string ans, in;
        cin >> n >> in;
        for(int i = 0; i<2*n-2; i++)
        {
            ans+=((in[i]=='S')?('E'):('S'));
        }
        cout << "Case #" << z+1 << ": " << ans << endl;
    }
}
