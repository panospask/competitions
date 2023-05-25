#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

int n, k, q;
vector<int> a, b;
vector<bool> inside;

pair<int, int> operator + (pair<int, int> a, pair<int, int> b)
{
    if (a.first > b.first)
        return a;
    else if (a.first < b.first)
        return b;
    else
        return mp(a.first, a.second + b.second);
}

void check_sim(void)
{
    pair<int, long int> totalans = mp(0, 0);
    for (int i = 0; i <= n - k; i++) {
        inside.assign(n, false);

        for (int j = i; j < i + k; j++)
            inside[b[j]] = true;

        int locans = 0;
        for (int j = 0; j < k; j++) {
            locans += inside[a[j]];
        }
        totalans = totalans + mp(locans, 1);

        for (int j = k; j < n; j++) {
            locans += inside[a[j]] - inside[a[j - k]];
            totalans = totalans + mp(locans, 1);
        }

    }

    printf("%d %d\n", totalans.first, totalans.second);
}

int main(void)
{
    scanf("%d %d %d", &n, &k, &q);
    a.resize(n);
    b.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    check_sim();
    while(q--) {
        int i;
        scanf("%d", &i);
        i--;
        swap(a[i], a[i+1]);

        check_sim();
    }

    return 0;
}