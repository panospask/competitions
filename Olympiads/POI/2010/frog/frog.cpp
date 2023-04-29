#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

ll m;
int n;
vector<int> pos;
vector<int> dest;
vector<vector<int>> place_after;
vector<int> component;
vector<bool> visited;
vector<bool> on_stack;
vector<bool> on_cycle;
stack<int> s;
vector<ii> joins_at;
vector<int> ans;
vector<int> cyclesize;
int components = 0;

void find_component(int node)
{
    if (visited[node]) {
        if (on_stack[node]) {
            // Create new cycle
            component[node] = components++;
            int sz = 1;
            while (s.top() != node) {
                component[s.top()] = component[node];
                joins_at[s.top()] = mp(s.top(), 0);
                on_cycle[s.top()] = true;
                sz++;
            }
            s.pop();
            cyclesize.push_back(sz);

            // Calculate the answer for the current node
            ll new_m = m % cyclesize[component[node]];
            // Do binary lifting

            int curn = node;
            while (dest[curn] != node) {
                ans[dest[curn]] = dest[ans[curn]];
                curn = dest[curn];
            }
        }
        return;
    }
    else {
        visited[node] = true;
        s.push(node);
        on_stack[node] = true;
        find_component(dest[node]);
        on_stack[node] = false;
        if (!on_cycle[node]) {
            s.pop();
            component[node] = component[dest[node]];
            joins_at[node] = mp(joins_at[dest[node]].first, joins_at[dest[node]].second + 1);

            // Calculate the answer for this node
            if (m < joins_at[node].second) {
                // Do binary lifting
            }
            else {
                int nodefind = joins_at[node].first - ((m - joins_at[node].second) % cyclesize[component[node]]);
                ans[node] = ans[nodefind];
            }
        }
    }
}

int main(void)
{
    ;
}