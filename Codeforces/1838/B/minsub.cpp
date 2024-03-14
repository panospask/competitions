#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int n;
vector<int> a;

void solve(void)
{
    scanf("%d", &n);
    a.resize(n);

    int onepos, twopos, npos;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        if (a[i] == 1)
            onepos = i;
        if (a[i] == 2)
            twopos = i;
        if (a[i] == n)
            npos = i;
    }

    int i, j;
    if (onepos > twopos)
        swap(onepos, twopos);

    if (npos > onepos && npos < twopos) {
        printf("1 1\n");
    }
    else if (npos < onepos) {
        printf("%d %d\n", npos + 1, onepos + 1);
    }
    else
        printf("%d %d\n", twopos + 1, npos + 1);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();
}