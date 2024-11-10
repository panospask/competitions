#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N;
vector<pi> vertices;

bool cmp(pi a, pi b)
{
    return a.first + a.second < b.first + b.second;
}

int main(void)
{
    scanf("%d", &N);

    vertices.resize(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        scanf("%d %d", &vertices[i].first, &vertices[i].second);
        if (vertices[i].first > vertices[i].second) {
            swap(vertices[i].first, vertices[i].second);
        }
    }

    sort(vertices.begin(), vertices.end(), cmp);

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans -= vertices[i].first;
    }
    for (int i = N; i < 2 * N; i++) {
        ans += vertices[i].second;
    }

    printf("%lld\n", ans);

    return 0;
}