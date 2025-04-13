#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e18;
const int BIG = 1e6;

int subtask;

int N, M;

vector<int> total_occurences;

vector<vector<bool>> found;
vector<vector<pi>> schedules;

// Values for each letter stored in v
int test_assignment(vector<int>& v) {
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans -= total_occurences[i] * v[i];
    }

    int winning = -1;
    for (int j = 0; j < M; j++) {
        winning = -1;
        for (int i = 0; i < schedules[j].size(); i++) {
            int let, pos;
            tie(let, pos) = schedules[j][i];
            if (let == -1) {
                break;
            }

            if (winning < v[let]) {
                if (pos != 0) {
                    ans += v[let];
                    ans -= winning;
                }
                winning = v[let];
            }

            int wins = schedules[j][i + 1].second - pos;
            ans += winning * wins;
        }
    }

    return ans;
}

int find(vector<int>& v, int left) {
    if (!left) {
        return test_assignment(v);
    }

    int ans = 1e9;
    for (int i = 0; i < N; i++) {
        if (v[i] == -1) {
            v[i] = left;
            ans = min(ans, find(v, left - 1));
            v[i] = -1;
        }
    }

    return ans;
}

int main(void) {
    scanf("%d", &subtask);
    scanf("%d %d", &N, &M);

    total_occurences.assign(N, 0);
    schedules.resize(M);
    found.assign(M, vector<bool>(N, false));

    for (int j = 0; j < M; j++) {
        string s;
        cin >> s;

        for (int i = 0; i < s.size(); i++) {
            int v = s[i] - 'A';
            total_occurences[v]++;
            if (!found[j][v]) {
                schedules[j].pb({v, i});
                found[j][v] = true;
            }
        }
        schedules[j].pb({-1, s.size()});
    }

    vector<int> v(N, -1);
    printf("%d\n", find(v, N));

    return 0;
}