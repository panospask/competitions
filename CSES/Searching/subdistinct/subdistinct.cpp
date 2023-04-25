#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> a;
map<int, int> valuecount;
int distinct;
long long ans;

void insert_val(int a)
{
    valuecount[a]++;
    if (valuecount[a] == 1)
        distinct++;
}

void remove_val(int a)
{
    valuecount[a]--;
    if (valuecount[a] == 0)
        distinct--;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    distinct = 0;
    ans = 0;

    int l = 0;
    for (int r = 0; r < n; r++) {
        insert_val(a[r]);
        while (distinct > k) {
            remove_val(a[l]);
            l++;
        }

        ans += (r - l) + 1;
    }

    printf("%lld\n", ans);
    return 0;
}