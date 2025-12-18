#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int MAXN = 250000;
const int BUCKETS = 500;

typedef pair<int, int> pi;

int N;

// Current location and finish location in each bucket
vector<int> cur, finish;

vector<pi> missions;

int main(void) {
    scanf("%d", &N);

    cur.resize(BUCKETS);
    finish.resize(BUCKETS);

    cur[0] = 0;
    for (int b = 1; b < BUCKETS; b++) {
        cur[b] = cur[b - 1] + b;
        MAXN -= b;
    }

    int c = 0;
    while (MAXN > 0) {
        c++;
        for (int b = 0; b < BUCKETS; b++) {
            cur[b] += b;
            MAXN--;
        }
    }

    // Bucket b has b + c elements
    
}