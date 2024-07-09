#include <bits/stdc++.h>

using namespace std;

int sum(int i1, int j1, int i2, int j2);
int M, N, A, B, C, D;

struct Rect {
    int x1, y1, x2, y2;

    int area(void) {
        x2 = min(x2, N - 1);
        y2 = min(y2, M - 1);
        return sum(x1, y1, x2, y2);
    }
};
Rect min(Rect a, Rect b)
{
    if (a.area() < b.area()) {
        return a;
    }
    else {
        return b;
    }
}
Rect DEFAULT = {0, 0, 1000, 1000};

struct ImprovedStack {
    stack<Rect> m;
    stack<Rect> s;

    ImprovedStack(void) {
        m.push(DEFAULT);
    }

    void push(Rect x) {
        s.push(x);
        m.push(min(m.top(), x));
    }
    void pop() {
        m.pop();
        s.pop();
    }
    Rect minrect(void) {
        return m.top();
    }
    Rect top(void) {
        return s.top();
    }
    bool empty(void) {
        return s.empty();
    }
};
struct ImprovedQueue {
    ImprovedStack s1, s2;

    void push(Rect x) {
        s2.push(x);
    }
    void pop() {
        if (s1.empty()) {
            while (!s2.empty()) {
                s1.push(s2.top());
                s2.pop();
            }
        }

        s1.pop();
    }
    Rect minrect(void) {
        return min(s1.minrect(), s2.minrect());
    }
    bool empty(void) {
        return s1.empty() && s2.empty();
    }
};

vector<vector<int>> pref;
vector<vector<int>> battlefield;
vector<ImprovedQueue> rows;
Rect op_b, op_c;

int sum(int i1, int j1, int i2, int j2)
{
    return pref[i2 + 1][j2 + 1] - pref[i1][j2 + 1] - pref[i2 + 1][j1] + pref[i1][j1];
}

// i: Row to be updated
// j: Column to be added to i
void update_row(int i, int j)
{
    // Not allowed to build at j because it is wall
    // But allowed to build at j - 1 (unavailable previously)
    // Same for i

    if (j < C || i < D) {
        return;
    }

    rows[i].push({i - D, j - C, i - 1, j - 1});

    // Check if an element should be removed because it became wall
    if (j - A + 1 >= 0) {
        rows[i].pop();
    }
}

void update_answer(Rect cur_b, Rect cur_c)
{
    if (cur_b.area() - cur_c.area() > op_b.area() - op_c.area()) {
        op_b = cur_b;
        op_c = cur_c;
    }
}

int main(void)
{
    scanf("%d %d %d %d %d %d", &M, &N, &A, &B, &C, &D);

    battlefield.resize(N, vector<int>(M));
    pref.resize(N + 1, vector<int>(M + 1));
    rows.resize(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &battlefield[i][j]);
        }
    }

    pref[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + battlefield[i - 1][j - 1];
        }
    }

    for (int c = 0; c < M; c++) {
        ImprovedQueue q;
        for (int r = 0; r < N; r++) {
            update_row(r, c);
            
            if (!rows[r].empty()) {
                q.push(rows[r].minrect());
            }

            if (r - B + 1 >= 0 && c - A + 1 >= 0) {
                q.pop();
                assert(!q.empty());

                update_answer({r - B + 1, c - A + 1, r, c}, q.minrect());
            }
        }
    }

    printf("%d %d\n%d %d\n", op_b.y1 + 1, op_b.x1 + 1, op_c.y1 + 1, op_c.x1 + 1);

    return 0;
}