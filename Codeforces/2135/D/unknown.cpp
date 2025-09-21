#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int W = 100;
const int BUCKET_SIZE = 21;
const int BUCKETS = (W + BUCKET_SIZE) / BUCKET_SIZE;

int cnt[W + 1];
pi result[BUCKETS];
int ans = 0;
int discrete = 2;

void precalc(void) {
    for (int i = 1; i < BUCKETS; i++) {
        result[i] = mp(0, 0);
        cnt[0]++;
    }

    while (discrete < BUCKETS) {
        ans++;
        for (int i = 1; i < BUCKETS; i++) {
            result[i].second++;
            if (result[i].second == i) {
                result[i].second = 0;
                
                // Change the values
                if (cnt[result[i].first] == 1) {
                    discrete--;
                }
                cnt[result[i].first]--;

                result[i].first++;

                if (cnt[result[i].first] == 0) {
                    discrete++;
                }
                cnt[result[i].first]++;
            }
        }
    }
}

void solve(void) {
    printf("? %d", ans);
    for (int t = 0; t < ans; t++) {
        printf(" %d", BUCKET_SIZE);
    }
    printf("\n");
    fflush(stdout);

    int res;
    scanf("%d", &res);

    int b = 0;
    while (result[b].first != res) {
        b++;
    }

    // We are in [BUCKET_SIZE * b, BUCKET_SIZE * (b + 1))
    int base_val = BUCKET_SIZE * b;

    printf("? %d", 2 * BUCKET_SIZE);
    for (int i = 0; i < BUCKET_SIZE; i++) {
        printf(" %d %d", base_val, i);
    }
    printf("\n");
    fflush(stdout);

    scanf("%d", &res);
    res -= BUCKET_SIZE;
    printf("! %d\n", base_val + BUCKET_SIZE - res - 1);
    fflush(stdout);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    precalc();

    while (t--) {
        solve();
    }

    return 0;
}