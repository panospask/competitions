#include <bits/stdc++.h>

using namespace std;

int replace_all(char array[], char replacement, int k, int n) 
{
    int swaps = 0;
    for (int i = 0; i < n; i+= k) {
        if (array[i] != replacement)
            swaps++;
    }

    return swaps;
}

int main(void)
{
    freopen("dna.in", "r", stdin);
    freopen("dna.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    char chain[n];
    for (int i = 0; i < n; i++) 
        cin >> chain[i];

    char most_pop;
    int min_swaps = INT_MAX;

    for (int i = 1; i <= k; i++) {
        if (k % i != 0 || k == i) {
            int swaps = 0;
            for (int j = 0; j < i && j < n; j++) {
                int as = 0, gs = 0, cs = 0, ts = 0;
                for (int x = j; x < n; x += i) {
                    if (chain[x] == 'A')
                        as++;
                    else if (chain[x] == 'G')
                        gs++;
                    else if (chain[x] == 'C')
                        cs++;
                    else if (chain[x] == 'T')
                        ts++;
                }

                if (as >= gs && as >= cs && as >= ts) 
                    most_pop = 'A';
                else if (ts >= gs && ts >= cs && ts >= as) 
                    most_pop = 'T';
                else if  (gs >= ts && gs >= cs && gs >= as) 
                    most_pop = 'G';
                else if  (cs >= ts && cs >= gs && cs >= as)
                    most_pop = 'C';           

                swaps += replace_all(&(chain[j]), most_pop, i, n - j);
                }
                if (swaps < min_swaps) {
                    min_swaps = swaps;

            }
        }
    }

    cout << min_swaps;
    
}