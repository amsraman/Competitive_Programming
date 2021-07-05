#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9+7;
int var_count = 0;

struct mat {
    const static int sz = 100;
    int m[100][100];
    mat() {
        memset(m,0,sizeof(m));
    }
    mat operator*(const mat &m2) {
        mat res;
        for(int i = 0; i<var_count+1; i++)
            for(int j = 0; j<var_count+1; j++)
                for(int k = 0; k<var_count+1; k++)
                    res.m[i][j] = (res.m[i][j]+(ll)m[i][k]*m2.m[k][j]%mod)%mod;
        return res;
    }
    static mat exp(mat &m, int b) {
        mat res = mat::id();
        while(b) {
            if(b&1)
                res = res*m;
            m = m*m, b>>=1;
        }
        return res;
    }
    static mat id() {
        mat res;
        for(int i = 0; i<sz; i++)
            for(int j = 0; j<sz; j++)
                res.m[i][j] = (i==j);
        return res;
    }
};

stack<int> loop_counters, exp_progress;
string first_token, next_token, return_var;
mat program = mat::id();
map<string,int> var_index;
stack<mat> levels;
bool done;

int main() {
    ifstream cin("cowbasic.in");
    ofstream cout("cowbasic.out");
    while(!done) {
        cin >> first_token;
        if(first_token == "}") {
            int counter = loop_counters.top();
            loop_counters.pop();
            program = mat::exp(program,counter);
            program = levels.top()*program;
            levels.pop();
        } else if(first_token == "RETURN") {
            cin >> return_var;
            cout << program.m[0][var_index[return_var]] << endl;
            done = true;
        } else {
            cin >> next_token;
            if(next_token == "MOO") {
                cin >> next_token;
                levels.push(program);
                program = mat::id();
                loop_counters.push(stoi(first_token));
            } else {
                if(!var_index.count(first_token))
                    var_index[first_token] = ++var_count;
                int cur_index = var_index[first_token];
                mat assignment = mat::id();
                assignment.m[cur_index][cur_index] = 0;
                do {
                    cin >> next_token;
                    if(next_token == "(") {
                        exp_progress.push(0);
                    } else if(next_token == ")") {
                        if(exp_progress.top() == 0) {
                            exp_progress.pop(), exp_progress.push(1);
                            cin >> next_token >> next_token;
                        } else {
                            exp_progress.pop();
                        }
                    } else if(isdigit(next_token[0])) {
                        assignment.m[0][cur_index] += stoi(next_token);
                    } else {
                        ++assignment.m[var_index[next_token]][cur_index];
                    }
                } while(!exp_progress.empty());
                program = program*assignment;
            }
        }
    }
}