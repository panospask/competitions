#include <bits/stdc++.h>

using namespace std;

const int NUM = 4;
const int MAXV = 1e5;
const int INF = 1e6;

int N[NUM];
vector<int> colours[NUM];

// For each element of a, find the smallest element of b that is larger than or
// equal to it
void find_min(const vector<int>& a, const vector<int>& b, vector<int>& m)
{
    int p2 = 0;
    for (int p1 = 0; p1 < a.size(); p1++) {
        while (p2 < b.size() && b[p2] < a[p1]) {
            p2++;
        }

        if (p2 < b.size()) {
            m[p1] = max(m[p1], b[p2]);
        }
        else {
            m[p1] = INF;
        }
    }
}

void counting_sort(vector<int>& a)
{
    vector<int> freq(MAXV + 1, 0);
    for (int i = 0; i < a.size(); i++) {
        freq[a[i]]++;
    }

    a.clear();
    for (int v = 0; v <= MAXV; v++) {
        while (freq[v]) {
            a.push_back(v);
            freq[v]--;
        }
    }
}

int main(void)
{
    for (int k = 0; k < NUM; k++) {
        scanf("%d", &N[k]);

        colours[k].resize(N[k]);
        for (int i = 0; i < N[k]; i++) {
            scanf("%d", &colours[k][i]);
        }

        counting_sort(colours[k]);
    }


    int ans = MAXV;
    int minv = 1;
    for (int k = 0; k < NUM; k++) {
        vector<int> m(N[k], -1);

        for (int l = 0; l < NUM; l++) {
            if (l == k) {
                continue;
            }

            find_min(colours[k], colours[l], m);
        }

        for (int i = 0; i < N[k]; i++) {
            if (m[i] != INF) {
                if (ans > m[i] - colours[k][i]) {
                    ans = m[i] - colours[k][i];
                    minv = colours[k][i];
                }
            }
        }
    }

    for (int k = 0; k < NUM; k++) {
        int i = 0;
        while (colours[k][i] < minv) {
            i++;
        }

        printf("%d ", colours[k][i]);
    }
    printf("\n");

    return 0;
}