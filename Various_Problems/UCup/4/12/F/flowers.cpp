#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

struct Query {
    int a, b, c;
    int idx;
};

bool operator < (const Query& a, const Query& b) {
    return a.a < b.a;
}

int N, Q;

vector<pi> segments;
vector<Query> queries;

int main(void) {
    scanf("%d %d", &N, &Q);

    segments.resize(N);
    queries.resize(Q);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        segments[i].first = x;
        segments[i].second = y;
    }

    for (int i = 0; i < Q; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        queries[i] = {a, b, c};
    }

    sort(segments.begin(), segments.end());
    sort(queries.begin(), queries.end());
}