#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int n;
set<int> interesting;
map<int, int> inter_val;
map<int, int> num_covered;
map<int ,int> cover_by_one;
pair<int, int> lifeguards[MAXN + 10];

int main(void)
{
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    scanf("%d", &n);
    int start, end;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &start, &end);
        interesting.insert(start);
        interesting.insert(end);
        inter_val[start]++;
        inter_val[end]--;

        lifeguards[i] = make_pair(start, end);
    }

    int prev_val = 0;
    int prevpoint = -1;
    int total_days = 0;
    for (auto point : interesting) {
        cover_by_one[point] = cover_by_one[prevpoint];
        if (prev_val == 1) {
            cover_by_one[point] += point - prevpoint;
        }
        if (prev_val >= 1) 
            total_days += point - prevpoint;

        num_covered[point] = inter_val[point] + prev_val;
        prev_val = num_covered[point];
        prevpoint = point;
    }

    int ans = 0;
    int days_lost;
    for (int i = 0; i < n; i++) {
        tie(start, end) = lifeguards[i];
        
        days_lost = cover_by_one[end] - cover_by_one[start];
        ans = max(ans, total_days - days_lost);
    }   

    printf("%d\n", ans);
    return 0;
}