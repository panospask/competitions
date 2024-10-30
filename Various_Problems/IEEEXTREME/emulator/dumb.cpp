#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
vector<pair<pi, int>> v;

int main(void)
{
    scanf("%d", &N);
    v.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &v[i].first.first, &v[i].first.second);
        v[i].second = i;
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < N; i += 3) {
        printf("%d %d %d\n", v[i].second, v[i + 1].second, v[i + 2].second);
    }
    return 0;
}