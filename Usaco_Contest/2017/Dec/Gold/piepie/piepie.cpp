#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct Pie {
    int bessielike;
    int elsielike;
    int id;
};

bool elsiefirst(const Pie& a, const Pie& b)
{
    return a.elsielike < b.elsielike;
}
bool bessiefirst(const Pie& a, const Pie& b)
{
    return a.bessielike < b.bessielike;
}

int n, d;
queue<int> q;
vector<int> steps;
vector<Pie> elsiepies;
vector<Pie> bessiepies;
vector<Pie> totalpies;

void proccess_neighbours(Pie p, vector<Pie>& searchpies)
{
    Pie lowest = p;
    lowest.bessielike -= d;
    lowest.elsielike -= d;
    int starting, ending;

    if (p.id < n) {
        // We have a Pie given by Elsie --> Search for which pies she could have recieved
        // [FROM THE BESSIE ARRAY]
        starting = lower_bound(searchpies.begin(), searchpies.end(), lowest, elsiefirst) - searchpies.begin();
        ending = upper_bound(searchpies.begin(), searchpies.end(), p, elsiefirst) - searchpies.begin();
    }
    else {
        // We have a Pie given by Bessie --> Search for which pies she could have recieved
        // [FROM THE ELSIE ARRAY]
        starting = lower_bound(searchpies.begin(), searchpies.end(), lowest, bessiefirst) - searchpies.begin();
        ending = upper_bound(searchpies.begin(), searchpies.end(), p, bessiefirst) - searchpies.begin();
    }

    for (int i = starting; i < ending; i++) {
        Pie cur = searchpies[i];

        if (steps[cur.id] != -1)
            continue;

        steps[cur.id] = steps[p.id] + 1;
        q.push(cur.id);
    }
    for (int i = ending - 1; i >= starting; i--) {
        Pie cur = searchpies[i];

        if (steps[cur.id] != -1)
            continue;

        steps[cur.id] = steps[p.id] + 1;
        q.push(cur.id);
    }
}

int main(void)
{
    freopen("piepie.in", "r", stdin);
    freopen("piepie.out", "w", stdout);

    scanf("%d %d", &n, &d);
    elsiepies.resize(n);
    bessiepies.resize(n);
    totalpies.resize(2 * n);
    steps.assign(2 * n, -1);

    for (int i = 0; i < 2* n; i++) {
        int e_like, b_like;
        scanf("%d %d", &e_like, &b_like);
        totalpies[i].bessielike = b_like;
        totalpies[i].elsielike = e_like;
        totalpies[i].id = i;

        if (i < n) {
            elsiepies[i] = totalpies[i];
            if (b_like == 0) {
                steps[i] = 1;
                q.push(i);
            }
        }
        else {
            bessiepies[i - n] = totalpies[i];
            if (e_like == 0) {
                steps[i] = 1;
                q.push(i);
            }
        }
    }

    sort(bessiepies.begin(), bessiepies.end(), elsiefirst);
    sort(elsiepies.begin(), elsiepies.end(), bessiefirst);

    while (!q.empty()) {
        Pie p = totalpies[q.front()];
        q.pop();

        if (p.id < n)
            proccess_neighbours(p, bessiepies);
        else
            proccess_neighbours(p, elsiepies);
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", steps[i]);

    return 0;
}