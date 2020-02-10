/*
ID: adityasund1
TASK: milk3
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int A, B, C;
bool visited[21][21] = {false};

void dfs(int a, int b)
{
    if(visited[a][b])
    {
        return;
    }
    visited[a][b] = true;
    dfs(a+min((C-a-b),(A-a)),b); //C to A
    dfs(a,b+min((C-a-b),(B-b))); //C to B
    dfs(0,b);//A to C
    dfs(a,0);//B to C
    dfs(a+min((A-a),b),b-min((A-a),b)); // B to A
    dfs(a-min(a,(B-b)),b+min(a,(B-b))); // A to B
}

int main()
{
    ifstream infile("milk3.in");
    ofstream outfile("milk3.out");
    infile >> A >> B >> C;
    dfs(0,0);
    int cnt = 0;
    for(int i = C; i>=0; i--)
    {
        if(visited[0][i])
        {
            if(cnt!=0)
            {
                outfile << " ";
            }
            outfile << C-i;
            cnt++;
        }
    }
    outfile << endl;
}
