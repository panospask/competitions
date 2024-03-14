#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct Mission {
    int a, b, c;
};

const int INF = 1e9;
const string names = {'L', 'M', 'W'};

int n;
int total_ids = 0;
vector<Mission> missions;
map<pi, pi> res1;
vector<pi> ids;

int ans_v = -INF;
pi ans_id = mp(-1 , -1);

bool comp = false;

void generate_answers(int id_latest, vector<string>& s)
{

    while (ids[id_latest].first != -1) {
        s.push_back("");
        for (int i = 0; i < 3; i++)
            if (ids[id_latest].second != i)
                s.back().push_back(names[i]);

        s.back().push_back('\n');

        id_latest = ids[id_latest].first;
    }

    reverse(s.begin(), s.end());
}

void next_mission(int cur, int final, int at_a, int at_b, int at_c, int id)
{
    if (cur == final) {
        int v1 = at_a - at_b;
        int v2 = at_b - at_c;
        if (!comp) {
            if (res1.find(mp(v1, v2)) == res1.end()) {
                res1[mp(v1, v2)] = mp(at_a, id);
            }
            else {
                if (res1[mp(v1, v2)].first < at_a)
                    res1[mp(v1, v2)] = mp(at_a, id);
            }
        }
        else {
            if (res1.find(mp(-v1, -v2)) != res1.end()) {
                pi r = res1[mp(-v1, -v2)];

                if (ans_v < at_a + r.first) {
                    ans_v = at_a + r.first;
                    ans_id = mp(r.second, id);
                }
            }
        }

        return;
    }

    // Exclude 0
    ids.push_back(mp(id, 0));
    next_mission(cur + 1, final, at_a, at_b + missions[cur].b, at_c + missions[cur].c, total_ids++);

    // Exclude 1
    ids.push_back(mp(id, 1));
    next_mission(cur + 1, final, at_a + missions[cur].a, at_b, at_c + missions[cur].c, total_ids++);

    // Exclude 2
    ids.push_back(mp(id, 2));
    next_mission(cur + 1, final, at_a + missions[cur].a, at_b + missions[cur].b, at_c, total_ids++);
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n;

    missions.resize(n);
    for (int i = 0; i < n; i++)
        cin >> missions[i].a >> missions[i].b >> missions[i].c;

    comp = false;
    ids.push_back(mp(-1, -1));
    next_mission(0, n / 2, 0, 0, 0, total_ids++);

    comp = true;
    ids.push_back(mp(-1, -1));
    next_mission(n / 2, n, 0, 0, 0, total_ids++);

    if (ans_v == -INF) {
        cout << "Impossible\n";
        return 0;
    }
    else {
        vector<string> l1, l2;
        generate_answers(ans_id.first, l1);
        generate_answers(ans_id.second, l2);

        for (auto& l : l1)
            cout << l;
        for (auto& l : l2)
            cout << l;
    }

    return 0;
}