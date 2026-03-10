#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> x;

int main(void) {
    scanf("%d", &N);

    x.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
    }

    // result at final straight is aX + b
    ll a = 0, b = 0;
    priority_queue<int> q;
    for (int i = 0; i < N; i++) {
        q.push(x[i]);
        q.push(x[i]);

        // The piecewise function has end val x - x[i]
        a += 1;
        b -= x[i];

        // Now remove last slope change point, and set b equal to the value there
        int l = q.top();
        q.pop();

        b = a * l + b;
        a = 0;
    }

    printf("%lld\n", b);
}