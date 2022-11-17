/*
ID: panos.p1
LANG: C++
TASK: lamps
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

vector<int> off;
vector<int> on;

int cur_state_num;
int counter;
int n;

set<vector<bool>> ans;

bool check_state(vector<bool>& state)
{
    //Check ON lamps
    for (auto test : on)
        if (!state[test])
            return false;

    //Check OFF lamps
    for (auto test : off)
        if (state[test])
            return false;

    ans.insert(state);
    return true;
}

vector<bool> mod_state(vector<bool>& state, int type)
{
    vector<bool> new_state = state;

    if (type == 1)
        for (int i = 1; i <= n; i++)
            new_state[i] = !(state[i]);

    else if (type == 2)
        for (int i = 1; i <= n; i+= 2)
            new_state[i] = !(state[i]);

    else if (type == 3)
        for (int i = 2; i <= n; i+= 2)
            new_state[i] = !(state[i]);

    else if (type == 4)
        for (int i = 1; i <= n; i+= 3)
            new_state[i] = !(state[i]);


    return new_state;
}

void sim_state(vector<bool> state, int steps, int last_activate)
{
    if ((counter - steps) % 2 == 0) {
        check_state(state);
        if (steps == counter)
            return;
    }

    for (int clight = last_activate + 1; clight <= 4; clight++)
        sim_state(mod_state(state, clight), steps + 1, clight);

    return;
}

int main(void)
{
    freopen("lamps.in", "r", stdin);
    freopen("lamps.out", "w", stdout);

    scanf("%d %d", &n, &counter);
    int curlamp;
    for (scanf("%d", &curlamp); curlamp != -1; scanf("%d", &curlamp)) 
        on.pb(curlamp);
    for (scanf("%d", &curlamp); curlamp != -1; scanf("%d", &curlamp))
        off.pb(curlamp);

    vector<bool> start_state(n + 5);
    for (int i = 1; i <= n; i++)
        start_state[i] = true;

    sim_state(start_state, 0, 0);

    for (auto state : ans) {
        int i = 0;
        for (auto lamp : state) {
            if (i > n)
                break;
            if (i != 0)
                printf("%d", (int)lamp);
            i++;
        }

        printf("\n");
    }

    if (ans.empty())
        printf("IMPOSSIBLE\n");

    return 0;
}