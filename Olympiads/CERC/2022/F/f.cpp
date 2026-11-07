#include <bits/stdc++.h>

using namespace std;

int N, M, K;

vector<vector<int>> A;
vector<vector<int>> cnt;

int main(void) {
    scanf("%d %d %d", &N, &M, &K);

    A.resize(N, vector<int>(M));
    vector<int> possible;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c;
            scanf(" %c", &c);

            A[i][j] = c - 'A';
        }
        possible.push_back(i);
    }

    while (possible.size() > 1) {
        cnt.assign(M, vector<int>(4, 0));

        for (auto i : possible) {
            for (int j = 0; j < M; j++) {
                cnt[j][A[i][j]]++;
            }
        }

        vector<int> nxt;

        for (auto i : possible) {
            int diff = 0;
            for (int j = 0; j < M; j++) {
                diff += (possible.size() - (cnt[j][A[i][j]]));
            }
            if (diff == (long long)K * (possible.size() - 1)) {
                nxt.push_back(i);
            }
        }

        if (nxt.size() == possible.size()) {
            break;
        }
        swap(nxt, possible);
    }

    printf("%d\n", (int)possible.back() + 1);
}