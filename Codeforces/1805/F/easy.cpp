#include <bits/stdc++.h>
#define MOD ((int)1e9 + 7)
#define MAXN 3000

using namespace std;

vector<long long int> cur_array;
vector<long long int> prv;

int next_one[MAXN + 2];
priority_queue<pair<long long int, int>, vector<pair<long long int, int>>, greater<pair<long long int, int>> > q;

long long ans = 0;

void calc_next_stage(void)
{
    if (prv.size() == 1) {
        ans += prv[0];
        return;
    }
    cur_array.clear();

    int n = prv.size();
    for (int i = 0; i < n - 1; i++) {
        q.push(make_pair(prv[i] + prv[i+1], i));
        next_one[i] = i + 1;
    }

    // Now make the cur_array
    for (int i = 0; i < n - 1; i++) {
        auto element = q.top(); q.pop();

        cur_array.push_back(element.first);
        next_one[element.second]++;
        if (next_one[element.second] < n)
            q.push(make_pair(prv[element.second] + prv[next_one[element.second]], element.second));
    }
    while (!q.empty())
        q.pop();

    long long int cur_comp = cur_array[0];
    for (int i = 0; i < n - 1; i++)
        cur_array[i] -= cur_comp;

    ans = ((2 * ans) % MOD ) + cur_comp % MOD;
    ans %= MOD;

    prv.resize(n-1);
    for (int i = 0; i < n - 1; i++)
        prv[i] = cur_array[i];

    cur_array.clear();
    calc_next_stage();
}

int n;
int main(void)
{
    scanf("%d", &n);
    prv.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &prv[i]);

    sort(prv.begin(), prv.end());
    calc_next_stage();
    printf("%lld\n", ans);
}