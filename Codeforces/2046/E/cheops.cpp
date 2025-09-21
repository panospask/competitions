#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9 + 1;

int N, M;
vector<int> a, b, s;

vector<vector<pi>> topic;
vector<int> all;
// maximum strength of any team 1 player
int maxstr;

// Difficulty by problem type
vector<int> diff;

int find(int v) {
    return lower_bound(all.begin(), all.end(), v) - all.begin();
}

void solve(void) {
    topic.clear();
    all.clear();

    scanf("%d %d", &N, &M);

    maxstr = 0;
    a.resize(N);
    b.resize(N);
    s.resize(N);
    int unused = 1;

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &a[i], &b[i], &s[i]);
        all.pb(s[i]);
    }

    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());

    while (unused <= N && all[unused - 1] == unused) {
        unused++;
    }

    topic.resize(all.size());
    for (int i = 0; i < N; i++) {
        s[i] = find(s[i]);
    }
    diff.assign(all.size(), INF);

    int K;
    scanf("%d", &K);
    vector<int> team1;
    team1.resize(K);
    for (int i = 0; i < K; i++) {
        scanf("%d", &team1[i]);
    }

    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int p;
        scanf("%d", &p);
        p--;

        maxstr = max(maxstr, a[p]);
        topic[s[p]].pb(mp(b[p], a[p]));
    }

    // Process each topic
    for (int i = 0; i < topic.size(); i++) {
        topic[i].pb(mp(INF, -1));
        sort(topic[i].begin(), topic[i].end());

        // Suffix maximum strength
        for (int j = topic[i].size() - 2; j >= 0; j--) {
            topic[i][j].second = max(topic[i][j].second, topic[i][j + 1].second);
        }
    }

    bool good = true;
    int lower_difficulty = -1;
    int upper_difficulty = INF;
    
    while (team1.size()) {
        int p = team1.back() - 1;
        team1.pop_back();

        if (b[p] <= maxstr) {
            good = false;
        }

        diff[s[p]] = min(diff[s[p]], b[p]);
        upper_difficulty = min(upper_difficulty, a[p]);

        // We want to beat those with same specialty (and higher wisdom) in strenth
        auto pos = lower_bound(topic[s[p]].begin(), topic[s[p]].end(), mp(b[p], -1)) - topic[s[p]].begin();
        lower_difficulty = max(lower_difficulty, topic[s[p]][pos].second);
    }

    if (!good || lower_difficulty >= upper_difficulty) {
        printf("-1\n");
    }
    else {
        vector<pi> problems;
        problems.pb({lower_difficulty + 1, unused});
        for (int i = 0; i < topic.size(); i++) {
            if (diff[i] != INF) {
                problems.pb({diff[i], all[i]});
            }
        }

        printf("%d\n", (int)problems.size());
        for (auto [d, t] : problems) {
            printf("%d %d\n", d, t);
        }
    }

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}