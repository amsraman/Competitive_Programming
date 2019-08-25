#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int t;
string e1, e2;

bool oper(bool a, bool b, char c)
{
    if(c=='&') return (a&b);
    if(c=='|') return (a|b);
    if(c=='^') return (a^b);
}

bool eval(string exp)
{
    vector<bool> val;
    vector<char> op;
    for(int i = 0; i<exp.length(); i++)
    {
        if(exp[i]=='(') op.push_back(exp[i]);
        else if((exp[i]=='0')||(exp[i]=='1')) val.push_back(exp[i]-'0');
        else if(exp[i]==')')
        {
            while((op.size()>0)&&(op[op.size()-1]!='('))
            {
                bool val2 = val[val.size()-1];
                val.pop_back();
                bool val1 = val[val.size()-1];
                val.pop_back();
                char curop = op[op.size()-1];
                op.pop_back();
                val.push_back(oper(val1,val2,curop));
            }
            op.pop_back();
        }
        else
        {
            while((op.size()>0)&&(op[op.size()-1]!='('))
            {
                bool val2 = val[val.size()-1];
                val.pop_back();
                bool val1 = val[val.size()-1];
                val.pop_back();
                char curop = op[op.size()-1];
                op.pop_back();
                val.push_back(oper(val1,val2,curop));
            }
            op.push_back(exp[i]);
        }
    }
    while(op.size()>0)
    {
        bool val2 = val[val.size()-1];
        val.pop_back();
        bool val1 = val[val.size()-1];
        val.pop_back();
        char curop = op[op.size()-1];
        op.pop_back();
        val.push_back(oper(val1,val2,curop));
    }
    return val[0];
}

int main()
{
    ifstream fin("mr_x.txt");
    ofstream fout("output.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> e1;
        e2 = e1;
        for(int i = 0; i<e1.length(); i++)
        {
            if(e1[i]=='x') e1[i] = '0';
            if(e1[i]=='X') e1[i] = '1';
            if(e2[i]=='x') e2[i] = '1';
            if(e2[i]=='X') e2[i] = '0';
        }
        fout << "Case #" << z+1 << ": " << (eval(e1)^eval(e2)) << endl;
    }
}
