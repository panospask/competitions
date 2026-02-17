#include <bits/stdc++.h>

using namespace std;

const string ans = "cerc";

int N = 3;
vector<pair<string, int>> A;
vector<int> found;

vector<int> res;

bool test(vector<pair<string, int>> A, string rem, int idx) {
    if (rem.empty()) {
        return true;
    }
    else if (idx == A.size()) {
        return false;
    }

    // Use current
    bool good = true;
    for (int i = 0; i < A[idx].first.size(); i++) {
        if (rem.size() == i || rem[i] != A[idx].first[i]) {
            return false;
        }
    }

    rem.erase(rem.begin(), rem.begin() + A[idx].first.size());
    res.push_back(A[idx].second);
    int v = test(A, rem, idx + 1);
    if (v) {
        return true;
    }
    res.pop_back();
    rem = A[idx].first + rem;

    return false;
}

int main(void) {
    A.resize(3);

    for (int i = 0; i < N; i++) {
        cin >> A[i].first;
        A[i].second = i;
    }

    sort(A.begin(), A.end());
    int v = 0;
    do {
        v = test(A, ans, 0);
        if (v) {
            break;
        }
    } while (next_permutation(A.begin(), A.end()));

    if (v == 0) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
        printf("%d\n", (int)res.size());
        for (int i = 0; i < res.size(); i++) {
            printf("%d ", res[i] + 1);
        }
        printf("\n");
    }
}