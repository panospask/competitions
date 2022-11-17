/*
ID: panos.p1
LANG: C++11
TASK: msquare
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

map<vector<int>, bool> visited;
vector<int> target;
string ans;
bool found = false;

void transform_A(vector<int>& cur)
{
    swap(cur[0], cur[4]);
    swap(cur[1], cur[5]);
    swap(cur[2], cur[6]);
    swap(cur[3], cur[7]);
}

void transform_B(vector<int>& cur)
{
    int temp = cur[3];
    for (int i = 3; i > 0; i--)
        cur[i] = cur[i-1];
    cur[0] = temp;
    temp = cur[7];
    for (int i = 7; i > 4; i--)
        cur[i] = cur[i-1];
    cur[4] = temp;
}

void transform_C(vector<int>& cur)
{
    int temp1 = cur[1], temp2 = cur[2];
    int temp3 = cur[5], temp4 = cur[6];
    cur[1] = temp3;
    cur[2] = temp1;
    cur[6] = temp2;
    cur[5] = temp4;
}

void dfs(vector<int> cur, string& way)
{
    if (visited[cur] || found)
        return;

    visited[cur] = true;
    if (cur == target) {
        found = true;
        ans = way;
        return;
    }

    vector<int> basic = cur;
    transform_A(basic);
    way.pb('A');
    dfs(basic, way);
    way.pop_back();

    if (!found) {
    basic = cur;
    transform_B(basic);
    way.pb('B');
    dfs(basic, way);
    way.pop_back();
    }

    if (!found) {
    basic = cur;
    transform_C(basic);
    way.pb('C');
    dfs(basic, way);
    way.pop_back();
    }

}

void bfs(vector<int> start)
{
    queue<pair<vector<int>, string>> q;
    string a;
    q.push(mp(start, a));
    visited[start] = true;

    pair<vector<int>, string> cur;
    while (!q.empty()) {
        cur = q.front(); q.pop();
        if (cur.first == target) {
            ans = cur.second;
        }

        auto t = cur.first;
        transform_A(t);
        if (!visited[t]) {
            visited[t] = true;
            q.push(mp(t, cur.second + 'A'));
        }
        t = cur.first;
        transform_B(t);
        if (!visited[t]) {
            visited[t] = true;
            q.push(mp(t, cur.second + 'B'));
        }
        t = cur.first;
        transform_C(t);
        if (!visited[t]) {
            visited[t] = true;
            q.push(mp(t, cur.second + 'C'));
        }
    }
}

int main(void)
{
    freopen("msquare.in", "r", stdin);
    freopen("msquare.out", "w", stdout);

    target.resize(8);
    // MAKE SURE ITS 1 - 2 - 3 - 4 - 8 - 7 - 6 - 5
    scanf("%d %d %d %d %d %d %d %d", &target[0], &target[1], &target[2], &target[3], &target[7], &target[6], &target[5], &target[4]);

    vector<int> cur;
    string a;
    cur.resize(8);
    cur[0] = 1;
    cur[1] = 2;
    cur[2] = 3;
    cur[3] = 4;
    cur[7] = 5;
    cur[6] = 6;
    cur[5] = 7;
    cur[4] = 8;

    bfs(cur);
    printf("%ld\n", ans.size());
    cout << ans <<'\n';
}