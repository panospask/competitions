#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))
#define mp make_pair
#define COMPLETED(var) ((1 << (var)) - 1)

using namespace std;

typedef pair<int, int> pi;

const int MAXB = 8;
const int MAXV = 1e9 + 1;

int N, M;
vector<vector<int>> a;
vector<int> found;

pi possible(int v)
{
    found.assign(1 << M, -1);
    for (int i = 0; i < N; i++) {
        int mask = 0;
        for (int j = 0; j < M; j++) {
            if (a[i][j] >= v) {
                mask += (1 << j);
            }
        }

        found[mask] = i;
        for (int s = 0; s < (1 << M); s++) {
            if ((s | mask) == COMPLETED(M) && found[s] != -1) {
                return make_pair(found[s], i);
            }
        }

    }

    return make_pair(-1, -1);
}

int main(void)
{
    scanf("%d %d", &N, &M);

    a.resize(N, vector<int>(M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int l = 0;
    int r = MAXV;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (possible(mid).first != -1) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    pi ans = possible(l);

    printf("%d %d\n", ans.first + 1, ans.second + 1);

    return 0;
}