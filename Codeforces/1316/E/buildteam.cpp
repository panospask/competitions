#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1 << pos)) != 0)

using namespace std;

typedef long long ll;

const ll INF = 1LL << 18;

struct Person {
    int a;
    vector<int> s;
};

int N, P, K;
vector<Person> people;

// dp[i][mask]: Strongest team if we select people up to i and fill the positions in mask
vector<vector<ll>> dp;

bool peoplecomp(const Person& a, const Person& b)
{
    return a.a > b.a;
}

void makemax(ll& a, ll b)
{
    if (a < b) {
        a = b;
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &P, &K);

    people.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &people[i].a);
    }
    for (int i = 0; i < N; i++) {
        people[i].s.resize(P);
        for (int j = 0; j < P; j++) {
            scanf("%d", &people[i].s[j]);
        }
    }
    sort(people.begin(), people.end(), peoplecomp);

    dp.assign(N + 1, vector<ll>(1 << P, -INF));
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int mask = 0; mask < (1 << P); mask++) {
            if (dp[i][mask] == -INF) {
                continue;
            }

            for (int pos = 0; pos < P; pos++) {
                if (!CHECK_BIT(mask, pos)) {
                    // Fill the position with the current member
                    makemax(dp[i + 1][mask + (1 << pos)], dp[i][mask] + people[i].s[pos]);
                }
            }

            int rem = K - (i - __builtin_popcount(mask));
            if (rem > 0) {
                // Audience seats remain emtpy, and since people are sorted by decreasing audience value
                // it is optimal to place current peson in the audience

                makemax(dp[i + 1][mask], dp[i][mask] + people[i].a);
            }  
            else {
                // Do not use the current person
                makemax(dp[i + 1][mask], dp[i][mask]);
            }          
        }
    }

    printf("%lld\n", dp[N][(1 << P) - 1]);

    return 0;
}