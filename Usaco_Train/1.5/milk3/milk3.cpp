/*
ID: panos.p1
LANG: C++
TASK: milk3
*/

#include <bits/stdc++.h>
#define pb push
#define mt make_triple

using namespace std;

struct triple {
    int first;
    int second;
    int third;

    bool operator == (struct triple b) {
        if (first == b.first)
            if (second == b.second)
                if (third == b.third)
                    return true;

        return false;
    }
};

bool operator < (const triple a, const triple b) {
        if (a.third != b.third)
            return a.third < b.third;
        if (a.second != b.second)
            return a.second < b.second;
        return a.first < b.first;
}

typedef struct triple Triple;

int acap, bcap, ccap;
set<Triple> ans;
set<Triple> visited;

Triple make_triple(int a, int b, int c)
{
    Triple i;
    i.first = a;
    i.second = b;
    i.third = c;

    return i;
}

Triple mod_cur(Triple& i, int& f, int& t)
{
    Triple new_i = i;
    int f_cur, t_cap, t_cur; 
    if (f == 1)
        f_cur = i.first;
    else if (f == 2)
        f_cur = i.second;
    else 
        f_cur = i.third;

    if (t == 1) {
        t_cap = acap;
        t_cur = i.first;
    }
    else if (t == 2) {
        t_cap = bcap;
        t_cur = i.second;
    }
    else {
        t_cap = ccap;
        t_cur = i.third;
    }

    int new_f, new_t;
    int can_get_t = t_cap - t_cur;

    if (f_cur > can_get_t) {
        new_t = t_cap;
        new_f = f_cur - can_get_t;
    }
    else {
        new_f = 0;
        new_t = t_cur + f_cur;
    }

    if (t == 1) 
        new_i.first = new_t;
    else if (t == 2)
        new_i.second = new_t;
    else 
        new_i.third = new_t;

    if (f == 1)
        new_i.first = new_f;
    else if (f == 2)
        new_i.second = new_f;
    else 
        new_i.third = new_f;

    return new_i;
}

void bfs(void)
{
    queue<Triple> q;

    q.push(mt(0, 0, ccap));
    visited.insert(mt(0, 0, ccap));

    Triple cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();

        if (cur.first == 0)
            ans.insert(cur);

        Triple ntrip;
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++) {
                if (i != j) {
                    ntrip = mod_cur(cur, i, j);
                    if (visited.find(ntrip) == visited.end()) {
                        visited.insert(ntrip);
                        q.pb(ntrip);
                    }
                }
            }
    }
}

int main(void)
{
    freopen("milk3.in", "r", stdin);
    freopen("milk3.out", "w", stdout);

    scanf("%d %d %d", &acap, &bcap, &ccap);

    bfs();

    int i = 0;
    int m = ans.size() - 1;
    for (auto& a : ans) {
        printf("%d", a.third);
        if (i != m)
            printf(" ");
        else 
            printf("\n");
        
        i++;
    }

    return 0;
}