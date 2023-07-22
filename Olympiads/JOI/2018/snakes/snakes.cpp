#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) ((val) & (1 << pos))

using namespace std;

int N, L, Q;

vector<int> a;

// Sum of all subsets that are fully contained inside the mask
vector<int> in_mask;
// Sum of all subsets that fully contain the mask
vector<int> at_least;
vector<int> A, B, C;

int CountNormal(int mask, int cpos)
{
    if (cpos == C.size())
        return a[mask];

    return CountNormal(mask, cpos + 1) + CountNormal(mask + (1 << C[cpos]), cpos + 1);
}

// Count by all submasks that include
int CountInclusion(int mask, int apos)
{
    if (apos == A.size()) {
        int mul = __builtin_popcount(mask) - B.size();
        if (mul % 2)
            mul = -1;
        else
            mul = 1;

        return at_least[mask] * mul;
    }

    return CountInclusion(mask, apos + 1) + CountInclusion(mask + (1 << A[apos]), apos + 1);
}

int CountExclusion(int mask, int bpos)
{
    if (bpos == B.size()) {
        int mul = B.size() - (__builtin_popcount(mask) - C.size());
        if (mul % 2)
            mul = -1;
        else
            mul = 1;

        return in_mask[mask] * mul;
    }

    return CountExclusion(mask, bpos + 1) + CountExclusion(mask + (1 << B[bpos]), bpos + 1);
}

int main(void)
{
    scanf("%d %d", &L, &Q);
    N = (1 << L);

    a.resize(N);
    in_mask.resize(N);
    at_least.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%1d", &a[i]);
        in_mask[i] = at_least[i] = a[i];
    }

    for (int i = 0; i < L; i++) {
        for (int s = 0; s < N; s++) {
            if (!CHECK_BIT(s, i)) {
                in_mask[s + (1 << i)] += in_mask[s];
            }
        }
    }

    for (int i = 0; i < L; i++) {
        for (int s = 0; s < N; s++) {
            if (CHECK_BIT(s, i)) {
                at_least[s - (1 << i)] += at_least[s];
            }
        }
    }

    while (Q--) {
        C.clear();
        A.clear();
        B.clear();
        char c;
        for (int i = L - 1; i >= 0; i--) {
            scanf(" %c", &c);
            if (c == '?')
                C.push_back(i);
            else if (c == '1')
                B.push_back(i);
            else
                A.push_back(i);
        }

        int ans;
        if (C.size() <= 6) {
            int m = 0;
            for (auto p : B)
                m += (1 << p);
            ans = CountNormal(m, 0);
        }
        else if (A.size() <= 6) {
            int m = 0;
            for (auto p : B)
                m += (1 << p);

            ans = CountInclusion(m, 0);
        }
        else {
            int m = 0;
            for (auto p : C)
                m += (1 << p);

            ans = CountExclusion(m, 0);
        }

        printf("%d\n", ans);
    }

    return 0;
}