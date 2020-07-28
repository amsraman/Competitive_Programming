#include <bits/stdc++.h>

using namespace std;

int t, n;
string in, out;
bool ans[50][50];

int main()
{
    freopen("travel_restrictions_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n >> in >> out;
        memset(ans,false,sizeof(ans));
        for(int i = 0; i<n; i++)
            ans[i][i] = true;
        for(int i = 0; i<n; i++)
            if(out[i]=='Y')
            {
                for(int j = i+1; j<n; j++)
                    ans[i][j] = (ans[i][j-1]&&in[j]=='Y'&&out[j-1]=='Y');
                for(int j = i-1; j>=0; j--)
                    ans[i][j] = (ans[i][j+1]&&in[j]=='Y'&&out[j+1]=='Y');
            }
        cout << "Case #" << _+1 << ": " << endl;
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
                cout << (ans[i][j]?'Y':'N');
            cout << endl;
        }
    }
}
