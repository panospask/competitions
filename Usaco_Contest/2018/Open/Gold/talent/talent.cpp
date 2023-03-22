#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXW (250 * 1000)
#define MAXN 250

using namespace std;

typedef pair<int, int> ii;

int maxtalent[MAXW + 1]; 
int n, w;
ii cows[MAXN + 2];
vector<ii> goodcows;
vector<ii> badcows;
int total_weight;

double ans = 0;

int main(void)
{
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);

    scanf("%d %d", &n, &w);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].first, &cows[i].second);
        if (cows[i].first < w) {
            goodcows.push_back(cows[i]);
            total_weight += cows[i].first;
        }
        else {
            badcows.push_back(cows[i]);
            ans = max(ans, (double)cows[i].second / cows[i].first);
        }
    }

    for (int i = 0; i <= total_weight; i++)
        maxtalent[i] = INT_MIN;

    maxtalent[0] = 0;
    for (auto cow : goodcows) {
        for (int i = total_weight; i >= cow.first; i--)
            maxtalent[i] = max(maxtalent[i], maxtalent[i - cow.first] + cow.second);
    }

    for (int i = total_weight; i >= 1; i--) {
        if (i >= w)
            ans = max(ans, (double)maxtalent[i] / i);
        
        for (auto booster : badcows) {
            int talent = maxtalent[i] + booster.second;
            int weight = i + booster.first;

            ans = max(ans, (double)talent / weight);
        }
    }

    printf("%d\n", (int) (1000*ans));
    return 0;
}