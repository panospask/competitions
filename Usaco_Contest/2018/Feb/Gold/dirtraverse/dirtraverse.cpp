#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int n;
vector<int> len;
vector<bool> isfile;
vector<vector<int>> kids;
vector<int> files_contained;
int total_files = 0;

vector<ll> distance_inside;
vector<ll> distance_outside;

void calculate_inside(int node)
{
    files_contained[node] = isfile[node];
    distance_inside[node] = 0;

    for (auto kid : kids[node]) {
        calculate_inside(kid);

        distance_inside[node] += distance_inside[kid];
        distance_inside[node] += len[kid] * files_contained[kid];
        files_contained[node] += files_contained[kid];
    }
}

void calculate_outside(int node, int par)
{
    distance_outside[node] = 0;
    if (par != -1) {
        distance_outside[node] = distance_inside[par] + distance_outside[par];
        distance_outside[node] -= distance_inside[node] + len[node] * files_contained[node];
        distance_outside[node] += (total_files - files_contained[node]) * 3;
    }

    for (auto kid : kids[node])
        calculate_outside(kid, node);
}

int main(void)
{
    freopen("dirtraverse.in", "r", stdin);
    freopen("dirtraverse.out", "w", stdout);

    ios::sync_with_stdio(false);

    cin >> n;

    kids.resize(n);
    isfile.assign(n, false);
    len.assign(n, 0);
    distance_inside.resize(n);
    distance_outside.resize(n);
    files_contained.assign(n, 0);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int k;
        cin >> k;

        isfile[i] = k == 0;
        total_files += isfile[i];
        len[i] = s.length() + !isfile[i];

        for (int j = 0; j < k; j++) {
            int ch;
            cin >> ch;
            ch--;
            kids[i].pb(ch);
        }
    }

    calculate_inside(0);
    calculate_outside(0, -1);

    ll ans = INF;
    for (int i = 0; i < n; i++)
        if (!isfile[i])
            ans = min(ans, distance_inside[i] + distance_outside[i]);

    cout << ans << endl;

    return 0;
}