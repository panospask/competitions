#include <bits/stdc++.h>
#define MOD(val, m) (val = (((val % m) + m) %m))


using namespace std;

int n, q;
string a, b;
vector<int> diff;
int total_diff;

void goodstrings(void)
{
    int add = 0;
    for (int i = 0; i < n; i++) {
        diff[i] = b[i] - a[i];
        MOD(diff[i], 26);
        if (i % 2)
            total_diff += diff[i];
        else
            total_diff -= diff[i];
    }

    MOD(total_diff, 26);
    if (total_diff == 0)
        printf("da\n");
    else
        printf("ne\n");
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n >> q;
    cin >> a >> b;
    diff.resize(n);

    for (int i = 0; i < n; i++) {
        a[i] -= 'a';
        b[i] -= 'a';
    }

    goodstrings();
    while (q--) {
        int p;
        char c;
        cin >> p >> c;
        p--;

        a[p] = c - 'a';
        int prv = diff[p];
        diff[p] = b[p] - a[p];

        if (p % 2)
            total_diff += diff[p] - prv;
        else
            total_diff -= diff[p] - prv;

        MOD(total_diff, 26);
        if (total_diff == 0)
            printf("da\n");
        else
            printf("ne\n");
    }

    return 0;
}