#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

int n;
ii candies[MAXN + 2];
int lis[MAXN + 2];
vector<ii> candies_caught[MAXN + 2];


// NOTE: It is important to sort segments of same left point by decreasing right point
// so they count as nested
bool compare_segments(ii a, ii b)
{
    if (a.first == b.first)
        return a.second > b.second;

    return a.first < b.first;
}

int main(void)
{
    scanf("%d", &n);
    int s, t;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &s, &t);
        candies[i] = make_pair(s - t, s + t);
    }

    // Sort the segments by left endpoint
    sort(candies, candies + n, compare_segments);

    for (int len = 0; len <= n; len++)
        lis[len] = INT_MAX;
    lis[0] = 0;
    for (int i = 0; i < n; i++) {
        int r_point = candies[i].second;
        
        int l = 0; // Condition: lis[l] < r_point
        int r = n; // Condition: lis[r] >= r_point
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (lis[mid] < r_point)
                l = mid;
            else 
                r = mid;
        }

        lis[l+1] = r_point;
        // Candies with the same lis length can be caught by the same wagon
        candies_caught[l+1].push_back(candies[i]);
    }

    int ans = 0;
    while (ans < n && lis[ans + 1] != INT_MAX)
        ans++;

    printf("%d\n", ans);
    for (int len = 1; len <= ans; len++) 
        for (ii c : candies_caught[len]) {
            int s = (long long)(c.first + c.second) / 2;
            int t = (long long)(c.second - c.first) / 2;

            printf("%d %d %d\n", s, t, len);
        }
    
    return 0;
}