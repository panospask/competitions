#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N;
vector<pi> many;
vector<int> single;

vector<pi> edges;

int main(void)
{
    scanf("%d", &N);

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        int a;
        scanf("%d", &a);
        cnt += a;

        if (a > 1) {
            many.pb(mp(a, i));
        }
        else {
            single.pb(i);
        }
    }

    if (cnt < 2 * N - 2) {
        printf("NO\n");
        return 0;
    }

    int diam = many.size() + min((int)single.size(), 2) - 1;

    if (single.size() > 0) {
        edges.pb(mp(many[0].second, single.back()));
        single.pop_back();
        many[0].first--;
    }

    for (int i = 1; i < many.size(); i++) {
        edges.pb(mp(many[i - 1].second, many[i].second));
        many[i - 1].first--;
        many[i].first--;
    }

    while (!single.empty()) {
        while (many.back().first == 0) {
            many.pop_back();
        }

        edges.pb(mp(many.back().second, single.back()));
        many.back().first--;
        single.pop_back();
    }

    printf("YES %d\n%d\n", diam, (int) edges.size());
    for (auto e : edges) {
        printf("%d %d\n", e.first + 1, e.second + 1);
    }
}