#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXK 5000
#define MAXN 5000
#define MAXM 100000
#define MOD 1000000007

using namespace std;

int n, m, k;
long long int total_combos[MAXK];
long long int combos_ending_in[MAXN + 3];
unordered_map<char, int> lines_rhyming;
pair<int, int> words[MAXN + 2];
set<int> rhymecats;

long long int calc_power(long long int a, long long int b, int mod)
{
    a %= mod;
    b %= mod;
    long long int c = 1;

    while (b) {
        if (b % 2)
            c = c * a % mod;
        
        a = a * a % mod;
        b /= 2;
    }

    return c;
}

int main(void)
{
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &words[i].first, &words[i].second);
        rhymecats.insert(words[i].second);
    }
    sort(words, words + n);
    
    for (int i = 0; i < m; i++) {
        char c;
        scanf(" %c", &c);
        lines_rhyming[c]++;
    }

    total_combos[0] = 1; // Only using no words can one get to 0
    for (int i = 0; i < k; i++) {
        for (int w = 0; w < n && words[w].first + i <= k; w++) {
            total_combos[i + words[w].first] += total_combos[i];
            total_combos[i + words[w].first] %= MOD;

            if (i + words[w].first == k) {
                combos_ending_in[words[w].second] += total_combos[i];
                combos_ending_in[words[w].second] %= MOD;
            }
        }
    }

    long long int ans = 1;
    for (auto different : lines_rhyming) {
        long long int val = 0;
        for (auto index : rhymecats) {
            val += calc_power(combos_ending_in[index], different.second, MOD);
            val %= MOD;
        }

        ans = ans * val % MOD;
    }

    printf("%lld\n", ans);
}