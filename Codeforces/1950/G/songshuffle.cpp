#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1 << pos)) != 0)
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef pair<string, string> ps;

int N;
vector<string> genres;
vector<string> writers;
vector<ps> initial;
vector<pi> songs;
vector<vector<bool>> dp;

void process(vector<string>& s)
{
    sort(s.begin(), s.end());
    s.resize(unique(s.begin(), s.end()) - s.begin());
}

int get(vector<string>& s, string& a)
{
    return lower_bound(s.begin(), s.end(), a) - s.begin();
}

void solve(void)
{
    genres.clear();
    writers.clear();

    cin >> N;
    initial.resize(N);
    songs.resize(N);

    for (int i = 0; i < N; i++) {
        string g, w;
        cin >> g >> w;

        initial[i] = mp(g, w);
        genres.pb(g);
        writers.pb(w);
    }

    // Coordinate compression
    process(genres);
    process(writers);
    for (int i = 0; i < N; i++) {
        songs[i] = mp(get(genres, initial[i].first), get(writers, initial[i].second));
    }

    dp.assign(1 << N, vector<bool>(N, false));
    for (int i = 0; i < N; i++) {
        dp[1 << i][i] = true;
    }

    int ans = 0;
    for (int s = 0; s < (1 << N); s++) {
        for (int last = 0; last < N; last++) {
            if (!dp[s][last]) {
                continue;
            }

            ans = max(ans, __builtin_popcount(s));

            for (int i = 0; i < N; i++) {
                if (CHECK_BIT(s, i)) {
                    // Already in set of current songs
                    continue;
                }
                if (songs[i].first == songs[last].first || songs[i].second == songs[last].second) {
                    dp[s | (1 << i)][i] = true;
                }
            }
        }
    }

    cout << N - ans << "\n";

    return;
}

int main(void)
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}