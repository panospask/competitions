#include <bits/stdc++.h>

using namespace std;

const int K = 100;

int N;
vector<bool> in_circle;
vector<int> ans;
vector<bool> use;

bool ask(int start, int moves)
{
    int ttl = 0;
    for (int i = 0; i < N; i++)
        ttl += use[i];
    printf("? %d %d %d", start + 1, moves, ttl);
    for (int i = 0; i < N; i++)
        if (use[i])
            printf(" %d", i + 1);
    printf("\n");

    fflush(stdout);

    int res;
    scanf("%d", &res);

    return res;
}

bool ask_range(int l, int r, int start, int moves)
{
    use.assign(N, false);
    for (int i = l; i < r; i++)
        use[i] = true;

    return ask(start, moves);
}
bool ask_range(int l, int r)
{
    return ask_range(l, r, 0, N);
}
bool ask_single(int i, int start, int moves)
{
    use.assign(N, false);
    use[i] = true;

    return ask(start, moves);
}

int main(void)
{
    scanf("%d", &N);

    in_circle.assign(N, false);
    use.resize(N);

    // Locate a room in the circle of 1
    int l = 0;
    int r = N;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (ask_range(l, mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    // Room with number l is in the same circle as 0
    int first = l;
    in_circle[first] = true;

    // Find the next k - 1 nodes
    for (int i = 1; i < K; i++) {
        int l = 0;
        int r = N;

        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (ask_range(l, mid, first, i)) {
                r = mid;
            }
            else {
                l = mid;
            }
        }
        if (l == first)
            break;
        in_circle[l] = true;
    }

    int updated = K;
    use = in_circle;
    while (updated >= 1) {
        updated = 0;
        for (int i = 0; i < N; i++) {
            if (in_circle[i])
                continue;

            if (ask(i, K)) {
                in_circle[i] = true;
                use[i] = true;
                updated++;
            }
        }
    }

    for (int i = 0; i < N; i++)
        if (in_circle[i])
            ans.push_back(i);

    printf("! %d\n", (int)ans.size());
    for (auto i : ans)
        printf(" %d", i + 1);
    printf("\n");

    return 0;
}