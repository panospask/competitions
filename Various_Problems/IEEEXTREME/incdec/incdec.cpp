#include <bits/stdc++.h>

using namespace std;

int N, M;
int ans = 0;

int proccess(vector<int> p)
{
    int i = find(p.begin(), p.end(), N - 1) - p.begin();
    int res = 0;
    if (i < N/2) {
        for (int j = i; j < N / 2; j++) {
            swap(p[j], p[j + 1]);
            res++;
        }
    }
    else {
        for (int j = i; j > N / 2; j--) {
            swap(p[j], p[j - 1]);
            res++;
        }
    }

    for (int i = 0; i <= N / 2; i++) {
        for (int j = 0; j < i; j++) {
            if (p[j] > p[i]) {
                res++;
            }
        }
    }
    for (int i = N - 1; i >= N / 2; i--) {
        for (int j = N - 1; j > i; j--) {
            if (p[j] > p[i]) {
                res++;
            }
        }
    }

    return res;
}

int main(void)
{
    scanf("%d %d", &N, &M);
    vector<int> p;
    for (int i = 0; i < N; i++) {
        p.push_back(i);
    }

    ans = proccess(p) % M;
    while(next_permutation(p.begin(), p.end())) {
        ans = (ans + proccess(p)) % M;
    }

    printf("%d\n", ans);

    return 0;
}