#include <bits/stdc++.h>
#define pb push_back

using namespace std;

bool suff(string a, string b)
{
    int d = a.size() - b.size();
    for (int i = 0; i < b.size(); i++) {
        if (a[i + d] != b[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    freopen("corrupt.in", "r", stdin);
    freopen("corrupt.out", "w", stdout);

    int c;

    string cur;
    cur.assign(7, '_');

    int t = 0;
    int v1 = 0, v2 = 0;
    int d1 = 0, d2 = 0;

    long long ans = 0;
    bool enable = true;
    while ((c = getchar()) != EOF) {
        cur.erase(cur.begin());
        cur.pb(c);
        
        if (t == 0) {
            if (suff(cur, "mul")) {
                t = 1;
                v1 = v2 = d1 = d2 = 0;
            }
            else if (suff(cur, "do()")) {
                enable = true;
            }
            else if (suff(cur, "don't()")) {
                enable = false;
            }
        }
        else if (t == 1) {
            if (c == '(') {
                t++;
            }
            else {
                t = 0;
            }
        }
        else if (t == 2) {
            if (isdigit(c) && d1 < 3) {
                v1 = v1 * 10 + c -'0';
                d1++;
            }
            else if (c == ',' && d1 > 0) {
                t++;
            }
            else {
                t = 0;
            }
        }
        else {
            if (isdigit(c) && d2 < 3) {
                v2 = v2 * 10 + c -'0';
                d2++;
            }
            else if (c == ')' && d2 > 0) {
                ans += v1 * v2 * enable;
                t = 0;
            }
            else {
                t = 0;
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}