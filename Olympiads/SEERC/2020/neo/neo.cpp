#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N;
vector<pi> people;

bool peoplesort(pi a, pi b)
{
    return a.first + a.second > b.first + b.second;
}

// What is the maximum obtainable profit if you rob x people and help x people;
ll profit(int x)
{
    priority_queue<int, vector<int>, greater<int>> robbed;
    multiset<int> helped;
    multiset<int> awaiting_help;

    ll opt = 0;
    ll cur = 0;

    // Insert the first x people into robbed
    for (int i = 0; i < x; i++) {
        robbed.push(people[i].first);
        cur += people[i].first;
    }
    // Everyone else into either helped or awaiting help
    for (int i = x; i < N; i++) {
        int v = people[i].second;
        if (helped.size() < x) {
            helped.insert(v);
        }
        else { 
            if (*helped.rbegin() > v) {
                helped.insert(v);
                v = *helped.rbegin();

                auto it = helped.end();
                it--;
                helped.erase(it);
            }

            awaiting_help.insert(v);
        }
    }

    for (auto v : helped) {
        cur -= v;
    }


    opt = cur;
    // Now move one by one the people to the robbed category
    for (int i = x; i + x < N; i++) {
        int v1, v2;
        tie(v1, v2) = people[i];
        if (v2 <= *helped.rbegin()) {

            cur += v2;
            helped.erase(helped.find(v2));

            cur -= *awaiting_help.begin();
            helped.insert(*awaiting_help.begin());
            awaiting_help.erase(awaiting_help.begin());
        }
        else {
            awaiting_help.erase(awaiting_help.find(v2));
        }

        if (v1 > robbed.top()) {
            cur -= robbed.top();
            robbed.pop();
            cur += v1;
            robbed.push(v1);
        }

        opt = max(opt, cur);
    }
    
    return opt;
}

int main(void)
{
    scanf("%d", &N);

    people.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &people[i].first);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &people[i].second);
    }
    sort(people.begin(), people.end(), peoplesort);

    int l = 0;
    int r = N / 2 + 1;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (profit(mid) >= 0) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    printf("%d\n", l);
    return 0;
}