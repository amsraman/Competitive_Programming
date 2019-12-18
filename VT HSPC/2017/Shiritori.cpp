#include <bits/stdc++.h>

using namespace std;

int n;
string words[100000];
map<string,bool> m;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> words[i];
    }
    m[words[0]] = true;
    for(int i = 1; i<n; i++)
    {
        if((words[i][0]!=words[i-1][words[i-1].length()-1])||(m[words[i]]))
        {
            cout << "Player " << 2-(i+1)%2 << " lost" << endl;
            return 0;
        }
        m[words[i]] = true;
    }
    cout << "Fair Game" << endl;
}
