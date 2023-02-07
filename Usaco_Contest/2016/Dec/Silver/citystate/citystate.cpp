#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 200000
#define umap unordered_map

using namespace std;

umap<string, umap<string, int>> state_codes;
int n;

void get_word(string& w)
{
    char  c;
    while ((c = getchar()) != EOF && c != ' ' && c != '\n') {
        w.pb(c);
    }
}

int main(void)
{
    freopen("citystate.in", "r", stdin);
    freopen("citystate.out", "w", stdout);

    scanf("%d", &n);
    getchar();
    string state, city;

    long int ans = 0;
    
    for (int i = 0; i < n; i++) {
        city.clear();
        state.clear();
        get_word(city);
        get_word(state);

        city = city.substr(0, 2);

        if (city != state) {
            if (state_codes.count(city) != 0) {
                if (state_codes[city].count(state) != 0)
                    ans += state_codes[city][state];
            }
        }

        state_codes[state][city]++;
    }

    printf("%ld\n", ans);
    return 0;
}