/* Idea:
 * Build a dag with nodes the strings and all the patterns that can produce the strings (e.g "____")
 */

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const char SPECIAL = '_';

int N, M, K;
vector<string> p;
vector<string> s;
vector<int> mt;
vector<int> ans;
vector<vector<int>> adj_list;

// pos[c]: Position of string with code c in p.
unordered_map<int, int> pos;

vector<bool> visited;
vector<bool> on_stack;

void negative(void)
{
    cout << "NO" << endl;
    exit(0);
}

int code(const string& s)
{
    int res = 0;
    int mul = 1;
    for (int i = 0; i < K; i++) {
        int v = (s[i] == SPECIAL) ? 26 : (s[i] - 'a');

        res += mul * v;
        mul *= 27;
    }

    return res;
}

bool match(const string& s, const string& t)
{
    for (int i = 0; i < K; i++) {
        if (s[i] != t[i] && t[i] != SPECIAL) {
            return false;
        }
    }

    return true;
}

// place t in the adjacency list of i
void place(string& t, int v, string& skip)
{
    int c = code(t);
    if (pos.count(c) && t != skip) {
        adj_list[v].pb(pos[c]);
    }

    for (int i = 0; i < K; i++) {
        if (t[i] != SPECIAL) {
            char prv = t[i];
            t[i] = SPECIAL;

            place(t, v, skip);

            t[i] = prv;
        }
    }
}

bool dfs(int node)
{
    if (visited[node]) {
        return !on_stack[node];
    }

    visited[node] = true;
    on_stack[node] = true;


    bool good = true;
    for (auto neigh : adj_list[node]) {
        good &= dfs(neigh);
    }

    ans.pb(node);
    on_stack[node] = false;

    return good;
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> N >> M >> K;

    p.resize(N);
    s.resize(M);
    mt.resize(M);
    adj_list.resize(N);
    visited.assign(N, false);
    on_stack.assign(N, false);

    for (int i = 0; i < N; i++) {
        cin >> p[i];
        pos[code(p[i])] = i;
    }
    for (int i = 0; i < M; i++) {
        cin >> s[i] >> mt[i];
        mt[i]--;
    }

    for (int i = 0; i < M; i++) {
        if (!match(s[i], p[mt[i]])) {
            negative();
        }

        place(s[i], mt[i], p[mt[i]]);
    }

    bool good = true;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            good &= dfs(i);
        }
    }

    if (!good) {
        negative();
    }

    cout << "YES" << endl;
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < N; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << endl;
}