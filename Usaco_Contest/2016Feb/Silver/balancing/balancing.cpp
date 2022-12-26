#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

typedef pair<int, int> ii;

ii cowcords[MAXN];
int n;
int minans = INT_MAX;
set<int> xcoords;
set<int> ycoords;

ii operator + (ii a, ii b)
{
    return mp(a.first + b.first, a.second + b.second);
}

void test_square(ii square)
{
    int tr = 0, tl = 0, br = 0, bl = 0;

    for (int i = 0; i < n; i++) {
        if (cowcords[i].first > square.first) {
            if (cowcords[i].second > square.second)
                tr++;
            else 
                br++;
        }
        else {
            if (cowcords[i].second > square.second)
                tl++;
            else   
                bl++;
        }
    }

    int sqmax = max(max(tr, tl), max(br, bl));

    if (sqmax < minans)
        minans = sqmax;
}

void test_cow(int i)
{
    ii sq_to_test = cowcords[i];
    test_square(sq_to_test + mp(1, 1));
    test_square(sq_to_test + mp(1, -1));
    test_square(sq_to_test + mp(-1, 1));
    test_square(sq_to_test + mp(-1, -1));
}

int main(void)
{
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cowcords[i].first, &cowcords[i].second);
        xcoords.insert(cowcords[i].first);
        ycoords.insert(cowcords[i].second);
    }

    sort(xcoords.begin(), xcoords.end());
    sort(ycoords.begin(), ycoords.end());

    printf("%d\n", minans);
    return 0;
}