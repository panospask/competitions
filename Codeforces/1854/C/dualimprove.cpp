#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6;

bool reversed = false;

int N;
vector<int> a;

int positive;
vector<pi> op;
pi largest;
pi smallest;

void make_positive(void)
{
    while (largest.f < abs(smallest.f)) {
        largest.f += largest.f;
        op.push_back(mp(largest.s, largest.s));
    }

    for (int i = 0; i < N; i++) {
        if (a[i] < 0) {
            a[i] += largest.f;
            op.push_back(mp(i, largest.s));
        }
    }
}

void take_prefix_sums(void)
{
    for (int i = 1; i < N; i++)
        op.push_back(mp(i, i - 1));
}
void print_operations(void)
{

    printf("%d\n", (int)op.size());
    for (auto& o : op) {
        if (reversed) {
            o.f = N - 1 - o.f;
            o.s = N - 1 - o.s;
        }
        printf("%d %d\n", o.f+ 1, o.s + 1);
    }
    printf("\n");
}

void swap_signs(void)
{
    reversed = true;

    positive = N - positive;
    swap(largest, smallest);

    largest.f *= -1;
    largest.s = N - 1 - largest.s;
    smallest.f *= -1;
    smallest.s = N - 1 - smallest.f;

    for (int i = 0; i < N; i++)
        a[i] *= -1;
    reverse(a.begin(), a.end());
}

void solve(void)
{
    scanf("%d", &N);

    op.clear();
    positive = 0;
    reversed = false;

    largest = mp(-INF, -INF);
    smallest = mp(INF, INF);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);

        if (a[i] >= 0)
            positive++;

        largest = max(largest, mp(a[i], i));
        smallest = min(smallest, mp(a[i], i));
    }

    if (smallest.f >= 0) {
        // Do nothing
        ;
    }
    else if (largest.f <= 0) {
        swap_signs();
    }
    else if (positive >= 13 || N - positive >= 13) {
        if (N - positive >= 13)
            swap_signs();
    }
    else {
        // Between 8 and 12 values for each sign
        if (largest.f < -smallest.f) {
            swap_signs();
        }
    }

    make_positive();
    take_prefix_sums();

    print_operations();

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}