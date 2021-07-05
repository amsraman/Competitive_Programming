#include <bits/stdc++.h>

using namespace std;

int t, n;

int main()
{
    cin >> t >> n;
    while(t--)
    {
        for(int i = 0, ret; i<n-1; i++)
        {
            cout << "M " << i+1 << " " << n << endl;
            cin >> ret;
            if(ret>i+1)
            {
                cout << "S " << i+1 << " " << ret << endl;
                cin >> ret;
                assert(ret == 1);
            }
        }
        cout << 'D' << endl;
        int res;
        cin >> res;
        assert(res == 1);
    }
}