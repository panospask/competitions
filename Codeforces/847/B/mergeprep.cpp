#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<int> a;
vector<vector<int>> seq;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < N; i++) {
        // Find first sequence in which a[i] can go
        int l = -1;
        int r = seq.size();

        while (l + 1 < r) {
            int mid = (l + r) / 2;

            if (seq[mid].back() >= a[i]) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        if (r == seq.size()) {
            seq.pb({a[i]});
        }
        else {
            seq[r].pb(a[i]);
        }
    }

    for (auto s : seq) {
        for (int i = 0; i < s.size(); i++) {
            printf("%d ", s[i]);
        }
        printf("\n");
    }

    return 0;
}