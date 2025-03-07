#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

int main(void)
{
    freopen("mergegame.in", "r", stdin);
    freopen("mergegame.out", "w", stdout);

    int type;
    scanf("%d", &type);

    scanf("%d", &N);
    
    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    while (A.size() > 1) {
        N = A.size();
        int minv = INT_MAX;
        for (int i = 0; i < N; i++) {
            minv = min(minv, A[i]);
        }

        for (int i = 1; i < N; i++) {
            if (A[i] == minv && A[i - 1] == minv) {
                A[i] = minv + 1;
                A[i - 1] = -1;
            }
        }

        vector<int> tmp;
        for (int i = 0; i < N; i++) {
            if (A[i] != minv && A[i] != -1) {
                tmp.push_back(A[i]);
            }
        }

        swap(tmp, A);
    }

    printf("%d\n", A[0]);

    return 0;
}