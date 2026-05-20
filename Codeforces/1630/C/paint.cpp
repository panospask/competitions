#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;
vector<int> early;
vector<int> deletion;

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    deletion.assign(N, -1);
    early.assign(N, -1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i]--;
        deletion[i] = i;

        if (early[A[i]] == -1) {
            early[A[i]] = i;
        }
    }

    int ans = 0;
    stack<int> s;
    for (int i = 0; i < N; i++) {
        while (!s.empty() && deletion[s.top()] > early[A[i]]) {
            deletion[i] = deletion[s.top()];
            s.pop();
            ans++;
        }
        s.push(i);
    }

    printf("%d\n", ans);
}