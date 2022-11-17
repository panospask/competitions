/*
ID: panos.p1
LANG: C++11
TASK: prefix
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

vector<string> prims;
string problem;
int ans;
int sz;

int maxstr;

int advance_with_string(int i, string& s)
{
    int to_go = s.size();

    for (int j = i; j > i - to_go && j >= 0; j--)
        if (s == problem.substr(j, to_go))
            return j - i + to_go;

    return 0;
}

int calc_length(void)
{
    ans = 0;
    
    int cnt = 0;

    int val = 0;
    while (cnt < prims.size()) {
        val = advance_with_string(ans, prims[cnt]);
        if (val > 0) {
            cnt = 0;
            ans += val;
        }
        else   
            cnt++;
    }

    return ans;
}

int main(void)
{
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);

    string s;
    while (true) {
        cin >> s;
        if (s[0] != '.') {
            prims.pb(s);
        }
        else 
            break;
    }

    char c;
    while (true) {
        cin >> c;
        if (c != '\0' && !cin.eof())
            problem.pb(c);
        else 
            if (cin.eof())
                break;
    }

    calc_length();

    printf("%d\n", ans);
    return 0;
}