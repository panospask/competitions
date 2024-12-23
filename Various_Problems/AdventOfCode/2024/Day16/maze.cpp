#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const ll INF = 1e18;

const pi dirs[4] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

struct State {
    int y, x;
    int dir;
    int cost;

    bool operator > (State b) {
        return cost < b.cost;
    }
};

vector<vector<int>> grid;
priority_queue<State> q;
vector<vector<vector<int>>> cost;
vector<vector<vector<int>>> visited;

int main(void)
{
    pi target;

    while (true) {
        auto cur =
    }
}