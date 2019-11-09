/*
ID: adityasund1
TASK: msquare
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <map>

using namespace std;

int main()
{
    ifstream infile("msquare.in");
    ofstream outfile("msquare.out");
    queue<string> q;
    map<string,string> m;
    q.push("12348765");
    m["12348765"] = "";
    while(!q.empty())
    {
        string s = q.front(), ar[8];
        q.pop();
        for(int i = 0; i<8; i++){ar[i] = s.substr(i,1);}
        string t1 = s.substr(4,4)+s.substr(0,4);
        string t2 = ar[3]+ar[0]+ar[1]+ar[2]+ar[7]+ar[4]+ar[5]+ar[6];
        string t3 = ar[0]+ar[5]+ar[1]+ar[3]+ar[4]+ar[6]+ar[2]+ar[7];
        if(!m.count(t1))
        {
            m[t1] = m[s]+"A";
            q.push(t1);
        }
        if(!m.count(t2))
        {
            m[t2] = m[s]+"B";
            q.push(t2);
        }
        if(!m.count(t3))
        {
            m[t3] = m[s]+"C";
            q.push(t3);
        }
    }
    string a = "", t;
    for(int i = 0; i<8; i++)
    {
        infile >> t;
        a+=t;
    }
    outfile << m[a.substr(0,4)+a.substr(7,1)+a.substr(6,1)+a.substr(5,1)+a.substr(4,1)].length() << endl;
    outfile << m[a.substr(0,4)+a.substr(7,1)+a.substr(6,1)+a.substr(5,1)+a.substr(4,1)] << endl;

}
