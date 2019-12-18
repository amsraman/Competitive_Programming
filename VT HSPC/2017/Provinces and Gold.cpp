#include <bits/stdc++.h>

using namespace std;

int g, s, c, p;

int main()
{
    cin >> g >> s >> c;
    p = 3*g+2*s+c;
    if(p>=8) cout << "Province or Gold" << endl;
    else if(p>=6) cout << "Duchy or Gold" << endl;
    else if(p>=5) cout << "Duchy or Silver" << endl;
    else if(p>=3) cout << "Estate or Silver" << endl;
    else if(p>=2) cout << "Estate or Copper" << endl;
    else cout << "Copper" << endl;
}
