#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int W = 100000;
const int BUCKET_SIZE = 334;
// const int BUCKETS = (W + BUCKET_SIZE) / BUCKET_SIZE;
const int BUCKETS = 1000;

int cnt[W + 1];
pi result[BUCKETS];
int ans = 0;
int discrete = 2;

int main(void) {
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

    printf("%d\n", BUCKETS);
    for (int i = 1; i < BUCKETS; i++) {
        printf("%d ", result[i].first);
    }
    printf("%d\n", ans);
}