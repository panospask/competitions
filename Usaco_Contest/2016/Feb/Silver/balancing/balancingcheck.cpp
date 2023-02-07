#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

typedef pair<int, int> ii;

ii cowcords[MAXN];
int mean;
set<int> xcoords;
set<int> ycoords;
int n;
int b;
int minans = INT_MAX;
vector<ii> minanssq;

void test_square(ii square)
{
    // if (square.first < 0 || square.first > b || square.second < 0 || square.second > b)
        // return;

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

    if (sqmax < minans) {
        minans = sqmax;
        minanssq.clear();
        minanssq.pb(square);
    }
    else if (sqmax == minans) 
        minanssq.pb(square);
}

int main(void) 
{
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cowcords[i].first, &cowcords[i].second);
        xcoords.insert(cowcords[i].first + 1);
        xcoords.insert(cowcords[i].first - 1);
        ycoords.insert(cowcords[i].second + 1);
        ycoords.insert(cowcords[i].second - 1);
    }

    for (auto i : xcoords)
        for (auto j : ycoords)
            test_square(mp(i, j));

    printf("%d\n", minans);
    for (auto p : minanssq)
        printf("%d %d\n", p.first, p.second);

    return 0;
}
