#include <bits/stdc++.h>

using namespace std;

multiset<int> differences;
multiset<int> values;

void erase(int v, multiset<int>& m)
{
    m.erase(m.find(v));
}
void insert(int v, multiset<int>& m)
{
    m.insert(v);
}

void remove_element(int v)
{
    auto it = values.find(v);

    int bef = -1, aft = -1;
    if (it != values.begin()) {
        it--;
        bef = *it;

        erase(v - bef, differences);
        it++;
    }

    it++;
    if (it != values.end()) {
        aft = *it;

        erase(aft - v, differences);
    }
    it--;

    if (bef != -1 && aft != -1) {
        insert(aft - bef, differences);
    }

    erase(v, values);
}

void insert_element(int v)
{
    int bef = -1, aft = -1;

    auto it = values.upper_bound(v);
    if (it != values.end()) {
        aft = *it;

        insert(aft - v, differences);
    }
    if (it != values.begin()) {
        it--;
        bef = *it;

        insert(v - bef, differences);
    }

    if (aft != -1 && bef != -1) {
        erase(aft - bef, differences);
    }

    insert(v, values);
}

void solve(void)
{
    differences.clear();
    values.clear();

    int N;
    scanf("%d", &N);

    vector<int> A(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        insert_element(A[i]);
    }

    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int i, v;
        scanf("%d %d", &i, &v);
        i--;

        remove_element(A[i]);
        A[i] = v;
        insert_element(A[i]);

        if (N == 1) {
            printf("%d ", A[0]);
            continue;
        }

        printf("%d ", *values.rbegin() + *differences.rbegin());
    }
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();
}