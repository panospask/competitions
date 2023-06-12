#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int n, k;
vector<int> a;
vector<int> cnt;
pi res;

int main(void)
{
    scanf("%d %d", &n, &k);

    a.resize(n);
    cnt.resize(1e6+ 5);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int l = 0;
    int r = 0;
    int diff = 0;
    int ans = 0;

    while (r < n) {
        cnt[a[r]]++;
        if (cnt[a[r]] == 1)
            diff++;
        r++;

        while (diff > k) {
            cnt[a[l]]--;
            if (cnt[a[l]] == 0)
                diff--;

            l++;
        }

        if(ans < r - l) {
            ans = r - l;
            res = mp(l, r);
        }
    }

    printf("%d %d\n", res.first + 1, res.second);

    return 0;
}