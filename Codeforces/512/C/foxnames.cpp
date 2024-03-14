#include <bits/stdc++.h>

using namespace std;

const int LETTERS = 26;

int n;
vector<vector<int>> adj_list;
vector<bool> vis;
vector<bool> on_stack;
vector<string> names;
string topsort;

bool dfs(int node)
{
    if (on_stack[node])
        return false;
    if (vis[node])
        return true;

    vis[node] = true;
    on_stack[node] = true;

    for (auto neigh : adj_list[node])
        if (dfs(neigh) == false)
            return false;

    topsort.push_back(node + 'a');
    on_stack[node] = false;
    return true;
}

int code(char c)
{
    return c - 'a';
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n;

    names.resize(n);
    adj_list.resize(LETTERS);


    for (int i = 0; i < n; i++)
        cin >> names[i];

    // Compare the names by 2 and find differences
    bool isgood = true;
    for (int i = 0; i < n - 1; i++) {
        // Compare i and i + 1;
        int let = 0;
        bool foundans = false;
        while (let < min(names[i].size(), names[i + 1].size()) && !foundans) {
            if (names[i][let] != names[i + 1][let]) {
                adj_list[code(names[i][let])].push_back(code(names[i + 1][let]));
                foundans = true;
            }
            else {
                let++;
            }
        }

        if (!foundans)
            isgood = names[i].size() < names[i + 1].size();
    }

    if (!isgood) {
        cout << "Impossible\n";
        return 0;
    }

    // Now build a topological ordering (if possible)
    vis.assign(LETTERS, false);
    on_stack.assign(LETTERS, false);

    isgood = true;
    for (int i = 0; i < LETTERS && isgood; i++) {
        if (!vis[i])
            isgood = dfs(i);
    }

    if (isgood) {
        reverse(topsort.begin(), topsort.end());
        cout << topsort << '\n';
    }
    else
        cout << "Impossible\n";

    return 0;
}