#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<vector<int>> A;
vector<vector<int>> source_spots;
vector<vector<int>> target_spots;

int main(void) {
    scanf("%d %d", &N, &K);

    source_spots.push_back({});
    target_spots.push_back({});
    A.assign(K, vector<int>(N, 0));
    for (int r = 0; r < K; r++) {
        for (int i = 0; i < N; i++) {
            scanf("%1d", &A[r][i]);
        }
    }

    for (int i = 0; i < N; i++) {
        source_spots.back().push_back(i);
        target_spots.back().push_back(i);
    }

    bool good = true;
    for (int r = 0; r < K - 1 && good; r++) {
        vector<vector<int>> src_new;
        vector<vector<int>> trg_new;

        for (int s = 0; s < source_spots.size(); s++) {
            // Current new source and target for each value
            vector<int> sn[2];
            vector<int> tn[2];

            for (auto p : source_spots[s]) {
                sn[A[r][p]].push_back(p);
            }
            for (auto p : target_spots[s]) {
                tn[A[r + 1][p]].push_back(p);
            }

            if (sn[0].size() != tn[0].size()) {
                good = false;
                break;
            }
            if (sn[0].size() > 0) {
                src_new.push_back(sn[0]);
                trg_new.push_back(tn[0]);
            }
            if (sn[1].size() > 0) {
                src_new.push_back(sn[1]);
                trg_new.push_back(tn[1]);
            }
        }

        swap(source_spots, src_new);
        swap(target_spots, trg_new);
    }

    if (!good) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    vector<int> p(N);
    for (int s = 0; s < source_spots.size(); s++) {
        for (int i = 0; i < source_spots[s].size(); i++) {
            p[source_spots[s][i]] = target_spots[s][i];
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", p[i] + 1);
    }
    printf("\n");
    return 0;
}