#include <bits/stdc++.h>

using namespace std;

int arr[4];
char ops[3] = {'+','-','*'};
set<int> ans;

int precedence(char op)
{
    if((op=='*')||(op=='/')) return 2;
    if((op=='+')||(op=='-')) return 1;
    return 0;
}

int oper(int a, int b, char op)
{
    if(op=='+') return a+b;
    if(op=='-') return a-b;
    if(op=='*') return a*b;
    if(op=='/') return a/b;
}

int eval(string exp)
{
    vector<int> val;
    vector<char> op;
    for(int i = 0; i<exp.length(); i++)
    {
        if(exp[i]=='(')
            op.push_back(exp[i]);
        else if(isdigit(exp[i]))
        {
            int cval = 0;
            while((i<exp.length())&&(isdigit(exp[i])))
                cval = cval*10+(exp[i]-'0'), i++;
            i--;
            val.push_back(cval);
        }
        else if(exp[i]==')')
        {
            while((op.size()>0)&&(op[op.size()-1]!='('))
            {
                int val2 = val[val.size()-1];
                val.pop_back();
                int val1 = val[val.size()-1];
                val.pop_back();
                char curop = op[op.size()-1];
                op.pop_back();
                val.push_back(oper(val1,val2,curop));
            }
            op.pop_back();
        }
        else
        {
            while((op.size()>0)&&(precedence(op[op.size()-1])>=precedence(exp[i])))
            {
                int val2 = val[val.size()-1];
                val.pop_back();
                int val1 = val[val.size()-1];
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
        int val2 = val[val.size()-1];
        val.pop_back();
        int val1 = val[val.size()-1];
        val.pop_back();
        char curop = op[op.size()-1];
        op.pop_back();
        val.push_back(oper(val1,val2,curop));
    }
    return val[0];
}

void gen(int x, string rf)
{
    if(x==3)
    {
        rf+=char('0'+arr[x]);
        if(rf.length()!=4 && eval(rf)>=0)
            ans.insert(eval(rf));
        return;
    }
    gen(x+1,rf+char('0'+arr[x]));
    for(int i = 0; i<3; i++)
        gen(x+1,rf+char('0'+arr[x])+ops[i]);
}

int main()
{
    for(int i = 0; i<4; i++)
        cin >> arr[i];
    sort(arr,arr+4);
    do {
        gen(0,"");
    } while(next_permutation(arr, arr+4));
    cout << ans.size() << endl;
}