#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);

    ll sum = 0;
    int evens = 0;
    int odds = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        sum += A[i];
        evens += (A[i] % 2 == 0);
        odds += (A[i] % 2 == 1);
    }

    int wins;
    if (sum % 2 == 0) {
        wins = 0;
    }
    else {
        // We have odd number of odds
        if (odds >= 3) {
            // Remove everything but 3 odd numbers
            // DON'T FORGET EXACTLY 3 ODD
            if (odds == 3 && evens == 0) {
                wins = 1;
            }
            else {
                wins = 0;
            }
        }
        // Only 1 odd
        // Only lose condition is 1 even
        else {
            if (evens == 1) {
                wins = 1;
            }
            else {
                wins = 0;
            }
        }
    }

    if (wins == 0) {
        printf("Moggity\n");
    }
    else {
        printf("Larpity\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        solve();
    }
}