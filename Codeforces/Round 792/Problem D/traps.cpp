#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back

typedef pair<long long int,int> ii;


bool use[500000];
vector<long long int> damage;
vector<ii> total_savings;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        damage.clear();
        total_savings.clear();

        int n, k;
        scanf("%d%d", &n, &k);
        memset(use, false, n);
        damage.resize(n);
        total_savings.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &damage[i]);
            use[i] = false;
        }
        
        for (int i = 0; i < n; i++) 
            total_savings[i] = mp(damage[i] - (n - i - 1), i);

        sort(total_savings.begin(), total_savings.end());
        
        int stacked = 0;
        long long int total_damage = 0;


        for (int i = n - 1; i >= n - k; i--) {
            use[total_savings[i].second] = true;
        }
        for (int i = 0; i < n; i++) {
            if (!use[i])
                total_damage += damage[i] + stacked;
            else
                stacked++;
        }

        printf("%lld\n", total_damage);
    }
}