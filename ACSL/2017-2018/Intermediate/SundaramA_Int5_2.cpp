//Aditya Sundaram
//Intermediate 5
//Contest 2

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int temp;
    string input, refe = "()[]", op = "+-*/";
    char interest;
    for(int aakashbalajikothapally = 0; aakashbalajikothapally<5; aakashbalajikothapally++){
    cout << "Input: ";
    getline(cin,input);
    int coun[4];
    for(int i = 0; i<4; i++)
    {
        coun[i] = 0;
    }
    for(int i = 0; i<input.length(); i++)
    {
        if(input[i]=='(')
        {
            coun[0]++;
        }
        else if(input[i]==')')
        {
            coun[1]++;
        }
        else if(input[i]=='[')
        {
            coun[2]++;
        }
        else if(input[i]==']')
        {
            coun[3]++;
        }
    }
    if(coun[0]!=coun[1])
    {
        int boun;
        if(coun[0]>coun[1])// )
        {
            boun = input.find('(');
            temp = 0;
            for(int i = boun+1; i<input.length(); i++)
            {
                if(op.find(input[i])<4)
                {
                    if(temp!=0)
                    {
                        cout << i+1 << endl;
                    }
                    temp++;
                }
                else if((input[i]=='[')||(input[i]==']'))
                {
                    if(input[i]==']')
                    {
                        cout << i+1 << endl;
                    }
                    temp = -1;
                    break;
                }
            }
            if(temp!=-1)
            {
                cout << input.length()+1 << endl;
            }
        }
        else if(coun[0]<coun[1])// (
        {
            boun = input.find(')');
            temp = 0;
            for(int i = boun-1; i>=0; i--)
            {
                if(op.find(input[i])<4)
                {
                    if(temp!=0)
                    {
                        cout << i+2 << endl;
                    }
                    temp++;
                }
                else if((input[i]=='[')||input[i]==']')
                {
                    if(input[i]=='[')
                    {
                        cout << i+2 << endl;
                    }
                    temp = -1;
                    break;
                }
            }
            if(temp!=-1)
            {
                cout << 1 << endl;
            }
        }
    }
    else if(coun[2]!=coun[3])
    {
        if(coun[2]<coun[3]) //[
        {
            temp = 0;
            coun[0] = 0, coun[1] = 0;
            for(int i = input.find(']')-1; i>=0; i--)
            {
                if(input[i]==']')
                {
                    temp = 0;
                }
                else if(input[i]=='(')
                {
                    coun[0]++;
                }
                else if(input[i]==')')
                {
                    coun[1]++;
                }
                else if(op.find(input[i])<4)
                {
                    if((temp>0)&&(coun[0]==coun[1]))
                    {
                        cout << i+2 << endl;
                    }
                    temp++;
                }
            }
            cout << 1 << endl;
        }
        else if(coun[2]>coun[3]) //]
        {
            temp = 0;
            coun[0] = 0, coun[1] = 0;
            for(int i = input.find('['); i<input.length(); i++)
            {
                if(input[i]=='[')
                {
                    temp = 0;
                }
                else if(input[i]=='(')
                {
                    coun[0]++;
                }
                else if(input[i]==')')
                {
                    coun[1]++;
                }
                else if(op.find(input[i])<4)
                {
                    if((temp>0)&&(coun[0]==coun[1]))
                    {
                        cout << i+1 << endl;
                    }
                    temp++;
                }
                else if(input[i]==']')
                {
                    cout << i+1 << endl;
                }
            }
            cout << input.length()+1 << endl;
        }
    }
    }
}
