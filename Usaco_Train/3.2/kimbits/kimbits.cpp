/*
ID: panos.p1
LANG: C++11
TASK: kimbits
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

string str;
long long int n, l, i;
set<string> total;
string ans;

long long int dfs(int onebits, int posfind)
{
    if (str.length() == n) {
        if (posfind == 1) {
            ans = str;
            return -1;
        }
        return 1;
    }

    // Append a 0
    str.pb('0');
    long long int ttlcnt1 = dfs(onebits, posfind);
    str.pop_back();
    if (ttlcnt1 == -1)
        return ttlcnt1;
    // Append a 1
    long long int ttlcnt2 = 0;
    if (onebits < l) {
        str.pb('1');
        ttlcnt2 = dfs(onebits + 1, posfind - ttlcnt1);
        str.pop_back();
        if (ttlcnt2 == -1)
            return ttlcnt2;
    }

    return ttlcnt1 + ttlcnt2;
}

int main(void)
{
    freopen("kimbits.in", "r", stdin);
    freopen("kimbits.out", "w", stdout);

    scanf("%d %d %d", &n, &l, &i);
    dfs(0, i);
    cout << ans;
    printf("\n");
    return 0;
}