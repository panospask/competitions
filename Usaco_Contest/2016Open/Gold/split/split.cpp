#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50000

using namespace std;

typedef pair<int, int> ii;

struct rect {
    int miny;
    int maxy;
    int minx;
    int maxx;

    multiset<int> cowsx;
    multiset<int> cowsy;

    void update_parameters(void) {
        if (!empty(cowsy)) {
            miny = *(cowsy.begin());
            maxy = *(cowsy.rbegin());
            minx = *(cowsx.begin());
            maxx = *(cowsx.rbegin());
        }
    }

    void add_cow(ii cow) {
        cowsx.insert(cow.first);
        cowsy.insert(cow.second);

        update_parameters();
    }

    void remove_cow(ii cow) {
        cowsx.erase(cowsx.find(cow.first));
        cowsy.erase(cowsy.find(cow.second));

        update_parameters();
    }

    long long int area(void) {
        update_parameters();
        return (long long int)(maxy - miny) * (maxx - minx);
    }

    rect(void) {
        maxy = 0;
        miny = 0;
        maxx = 0;
        minx = 0;
        cowsx.clear();
        cowsy.clear();
    }

    void clear(void) {
        maxy = 0;
        miny = 0;
        maxx = 0;
        minx = 0;
        cowsx.clear();
        cowsy.clear();
    }
};
typedef struct rect Rect;

ii cows[MAXN + 5];
int n;

bool ycomp(ii a, ii b)
{
    if (a.second == b.second)
        return a.first < b.first;
    
    return a.second < b.second;
}

int main(void)
{
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);

    scanf("%d", &n);
    int maxx = 0, minx = INT_MAX, maxy = 0, miny = INT_MAX;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].first, &cows[i].second);
        maxx = max(cows[i].first, maxx);
        minx = min(cows[i].first, minx);
        maxy = max(cows[i].second, maxy);
        miny = min(cows[i].second, miny);
    }

    // Build the rectangles on top of each other
    sort(cows, cows + n);
    long long int min_area = INT_MAX;
    Rect sq_a, sq_b;
    for (int i = 0; i < n; i++)
        sq_b.add_cow(cows[i]);
    min_area = sq_a.area() + sq_b.area();

    // printf("%lld\n", min_area);

    for (int i = 0; i < n - 1; i++) {
        sq_a.add_cow(cows[i]);
        sq_b.remove_cow(cows[i]);
        if (i != n - 1 && cows[i].first == cows[i + 1].first)
            continue;

        min_area = min(min_area, sq_a.area() + sq_b.area());
    }
    // printf("%lld\n", min_area);

    // Now build side by side 
    sort(cows, cows + n, ycomp);
    sq_a.clear(); sq_b.clear();
    for (int i = 0; i < n; i++)
        sq_b.add_cow(cows[i]);
    min_area = min(min_area, sq_a.area() + sq_b.area());
    for (int i = 0; i < n - 1; i++) {
        sq_a.add_cow(cows[i]);
        sq_b.remove_cow(cows[i]);
        if (i != n - 1 && cows[i].second == cows[i + 1].second)
            continue;

        min_area = min(min_area, sq_a.area() + sq_b.area());
    }

    // printf("%lld\n", min_area);
    printf("%lld\n", (long long int)(maxx - minx) * (maxy - miny) - min_area);
    return 0;
}