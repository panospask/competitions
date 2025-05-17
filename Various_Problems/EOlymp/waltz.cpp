#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> boys, girls;

int main(void) {
    scanf("%d %d", &N, &M);

    boys.resize(N);
    girls.resize(M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &boys[i]);
    }
    for (int j = 0; j < M; j++) {
        scanf("%d", &girls[j]);
    }

    multiset<int> s;
    // Place all girls in s
    for (int j = 0; j < M; j++) {
        // O(logM) per insert
        s.insert(girls[j]);
    } 

    // Find match for many boys
    int matches = 0;
    for (int i = 0; i < N; i++) {
        // O(M) !!! BAD
        // lower_bound(s.begin(), s.end(), boys[i]);
        // O(logM) !!! GOOD
        auto it = s.upper_bound(boys[i]);

        if (it == s.begin()) {
            // We are at the beginning
            continue;
        }

        it = prev(it);

        // Match chosen
        matches++;
        s.erase(it);
    }

    printf("%d\n", matches);

    return 0;
}