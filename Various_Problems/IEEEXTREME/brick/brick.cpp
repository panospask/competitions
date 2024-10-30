#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N, X;
int ans = 0;
vector<int> A;
vector<int> place;
vector<int> inv;
vector<pi> srt;

int main(void)
{
    scanf("%d %d", &N, &X);

    place.resize(N);
    A.resize(N);
    inv.resize(N);
    srt.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &srt[i].first);
        srt[i].second = i;
    }
    sort(srt.rbegin(), srt.rend());
    for (int i = 0; i < N; i++) {
        A[i] = srt[i].first;
        inv[i] = srt[i].second;
    }

    int ans = 0;
    int p = 0;
    for (int i = 0; i < N; i++) {
        if (A[p] >= A[i] + X) {
            place[i] = place[p];
            p++;
        }
        else {
            place[i] = ans++;
        }
    }

    vector<vector<int>> stacks(ans);
    for (int i = 0; i < N; i++) {
        stacks[place[i]].pb(i);
    }

    printf("%d\n", ans);
    for (int i = 0; i < ans; i++) {
        printf("%d ", (int)stacks[i].size());
        for (int j = 0; j < stacks[i].size(); j++) {
            printf("%d ", A[stacks[i][j]]);
        }
        printf("\n");
    }

    return 0;
}