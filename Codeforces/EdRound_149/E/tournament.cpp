#include <bits/stdc++.h>
#define MOD 998244353

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int k, n;
vector<int> possible_teams;
vector<pi> seeds;
vector<int> places_filled;
vector<ll> fact;

int msb(int i)
{
    if (i == 0)
        return 0;
    else
        return 32 - __builtin_clz(i);
}

bool isless(int a, int b)
{
    return msb(a) < msb(b);
}

bool customsort(const pi& a, const pi& b)
{
    return a.first > b.first;
}

int main(void)
{
    scanf("%d", &k);
    n = 1 << k;

    fact.resize(n);
    fact[0] = 1;
    for (int i = 1; i < fact.size(); i++)
        fact[i] = fact[i - 1] * i % MOD;

    places_filled.assign(n + 1, -1);
    possible_teams.resize(n);

    possible_teams[0] = 1;
    for (int i = 1; i < k; i++)
        possible_teams[i] = 1 << (i - 1);

    for (int i = 0; i < n; i++) {
        int team;
        scanf("%d", &team);
        team--;
        if (team != -1)
            seeds.push_back(make_pair(team, i));
    }

    sort(seeds.begin(), seeds.end(), customsort);

    for (int i = 0; i < seeds.size(); i++) {
        int place, team;
        tie(team, place) = seeds[i];
        if (places_filled[place] > team) {
            printf("0\n");
            return 0;
        }
        else {
            int fill_places = (1 << (k - msb(team)));

            int startpos;
            if (place < fill_places)
                startpos = 0;
            else
                startpos = place - place % (1 << (msb(fill_places)-1));

            for (int i = startpos; i < startpos + fill_places; i++)
                places_filled[i] = max(places_filled[i], team);

            possible_teams[msb(team)] = max(possible_teams[msb(team)] - 1, 1);
        }
    }

    ll ans = 1;
    for (int i = 0; i < k; i++) {
        ans = ans * fact[possible_teams[i]] % MOD;
    }

    printf("%lld\n", ans);
}