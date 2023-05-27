#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
set<int> days;
map<int, int> compress;

struct project {
    int start;
    int end;
    int p;

    void readproject(void) {
        scanf("%d %d %d", &start, &end, &p);
        days.insert(start);
        days.insert(end);
    }
};
typedef struct project Project;

vector<Project> projects;

int main(void)
{
    scanf("%d", &n);
    projects.resize(n);

    for (int i = 0; i < n; i++) {
        projects[i].readproject();
    }

    int d = 1;
    for (auto day : days) {
        compress[day] = d++;
    }
    compress[0] = 0;

    vector<vector<ll>> dp(d, vector<ll>(2));
    vector<vector<Project>> starts_at;
    starts_at.resize(d);
    for (int i = 0; i < n; i++)
        starts_at[compress[projects[i].start]].push_back(projects[i]);

    for (int i = 1; i < d; i++) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = max(dp[i][0], dp[i][1]);

        for (auto p : starts_at[i]) {
            int e = compress[p.end];
            dp[e][1] = max(dp[e][1], dp[i][0] + p.p);
        }
    }

    printf("%lld\n", dp[d-1][1]);
}