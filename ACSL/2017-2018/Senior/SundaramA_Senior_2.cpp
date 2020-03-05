#include <iostream>
#include <string>

using namespace std;

int main()
{
    string input, op = "+-*/";
    for(int aakashbalajikothapally = 0; aakashbalajikothapally<5; aakashbalajikothapally++){
    cout << "Input: ";
    getline(cin,input);
    int temp, coun[6] = {0,0,0,0,0,0};
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
        else if(input[i]=='{')
        {
            coun[4]++;
        }
        else if(input[i]=='}')
        {
            coun[5]++;
        }
    }
    if(coun[0]!=coun[1])
    {
        int boun;
        if(coun[0]<coun[1])// (
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
                else if(((input[i]=='[')||(input[i]==']'))||((input[i]=='{')||(input[i]=='}')))
                {
                    if((input[i]=='[')||(input[i]=='{'))
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
        else if(coun[0]>coun[1])// )
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
                else if(((input[i]=='[')||(input[i]==']'))||((input[i]=='{')||(input[i]=='}')))
                {
                    if((input[i]==']')||(input[i]=='}'))
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
    }
    else if(coun[2]!=coun[3])
    {
        int boun;
        int pare[2] = {0,0};
        if(coun[2]<coun[3])// [
        {
            temp = 0;
            boun = input.find(']');
            for(int i = boun; i>=0; i--)
            {
                if(input[i]=='(')
                {
                    pare[0]++;
                }
                else if(input[i]==')')
                {
                    pare[1]++;
                }
                else if(op.find(input[i])<4)
                {
                    if(pare[0]==pare[1])
                    {
                        if(temp!=0)
                        {
                            cout << i+2 << endl;
                        }
                    }
                    temp++;
                }
                else if((input[i]=='{')||(input[i]=='}'))
                {
                    if(input[i]=='{')
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
        else if(coun[2]>coun[3])// ]
        {
            temp = 0;
            boun = input.find('[');
            for(int i = boun; i<input.length(); i++)
            {
                if(input[i]=='(')
                {
                    pare[0]++;
                }
                else if(input[i]==')')
                {
                    pare[1]++;
                }
                else if(op.find(input[i])<4)
                {
                    if(pare[0]==pare[1])
                    {
                        if(temp!=0)
                        {
                            cout << i+1 << endl;
                        }
                    }
                    temp++;
                }
                else if((input[i]=='{')||(input[i]=='}'))
                {
                    if(input[i]=='}')
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
    }
    else if(coun[4]!=coun[5])
    {
        int prev[4] = {0,0,0,0};
        int boun;
        if(coun[4]<coun[5])// {
        {
            boun = input.find('}');
            temp = 0;
            for(int i = boun; i>=0; i--)
            {
                if(input[i]=='(')
                {
                    prev[0]++;
                }
                else if(input[i]==')')
                {
                    prev[1]++;
                }
                else if(input[i]=='[')
                {
                    prev[2]++;
                }
                else if(input[i]==']')
                {
                    prev[3]++;
                }
                else if(op.find(input[i])<4)
                {
                    if((prev[0]==prev[1])&&(prev[2]==prev[3]))
                    {
                        if(temp!=0)
                        {
                            cout << i+2 << endl;
                        }
                    }
                    temp++;
                }
            }
            cout << 1 << endl;
        }
        else if(coun[4]>coun[5])// }
        {
            boun = input.find('{');
            temp = 0;
            for(int i = boun; i<input.length(); i++)
            {
                if(input[i]=='(')
                {
                    prev[0]++;
                }
                else if(input[i]==')')
                {
                    prev[1]++;
                }
                else if(input[i]=='[')
                {
                    prev[2]++;
                }
                else if(input[i]==']')
                {
                    prev[3]++;
                }
                else if(op.find(input[i])<4)
                {
                    if((prev[0]==prev[1])&&(prev[2]==prev[3]))
                    {
                        if(temp!=0)
                        {
                            cout << i+1 << endl;
                        }
                    }
                    temp++;
                }
            }
            cout << input.length()+1 << endl;
        }
    }
    }
    return 0;
}
