#include <bits/stdc++.h>
#define MAXN 200000
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

bool compfunc (int a, int b)
{
    return b < a;
}
int n, k;
ii movies[MAXN + 5];
int avail_members;
multiset<int, decltype(compfunc)*> finishing_times(compfunc);


int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &movies[i].second, &movies[i].first);
    }
    avail_members = k;
    sort(movies, movies + n);

    int watched = 0;
    for (int i = 0; i < n; i++) {
        if (avail_members > 0) {
            watched++;
            finishing_times.insert(movies[i].first);
            if (finishing_times.lower_bound(movies[i].second) != finishing_times.end())
                finishing_times.erase(finishing_times.lower_bound(movies[i].second));
            else 
                avail_members--;
        }
        else {
            if (finishing_times.lower_bound(movies[i].second) != finishing_times.end()) {
                finishing_times.erase(finishing_times.lower_bound(movies[i].second));
                watched++;
                finishing_times.insert(movies[i].first);
            }
        }
    }

    printf("%d\n", watched);
    return 0;
}