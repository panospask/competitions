#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

typedef pair<int, int> ii;

ii cowcords[MAXN];
int n;
int b;
int minans = INT_MAX;
vector<ii> minanssq;

void test_square(ii square)
{
    if (square.first < 0 || square.first > b || square.second < 0 || square.second > b)
        return;

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

    scanf("%d %d", &n, &b);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &cowcords[i].first, &cowcords[i].second);

    for (int i = 0; i <= b; i += 2)
        for (int j = 0; j <= b; j += 2)
            test_square(mp(i, j));

    printf("%d\n", minans);
    for (auto p : minanssq)
        printf("%d %d\n", p.first, p.second);

    return 0;
}
