/*
ID: panos.p1
LANG: C++11
TASK: window
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int top = 0, bottom = 0;


struct window {
    int x1, y1, x2, y2;
    int level;

    window(int i, int j, int k, int l, int lvl) {
        this->x1 = min(i, k);
        this->y1 = min(j, l);
        this->x2 = max(i, k);
        this->y2 = max(j, l);
        this->level = lvl;
    }
    window(void) {
        ;
    }

    void operator = (struct window b) {
        this->x1 = b.x1;
        this->x2 = b.x2;
        this->y1 = b.y1;
        this->y2 = b.y2;
        this->level = b.level;
    }

    double area(void) {
        return (x2 - x1) * (y2 - y1);
    }
};
typedef struct window Window;

map<char, Window> win;
vector<Window> overlapping;

bool check_overlap(Window& a, Window& b)
{
    if (a.y1 >= b.y2 || b.y1 >= a.y2 || a.x1 >= b.x2 || b.x1 >= a. x2)
        return false;

    return true;
}

double getArea(Window& cur, int ind)
{
    while (ind < overlapping.size() && !check_overlap(cur, overlapping[ind]))
        ind++;

    if (ind == overlapping.size())
        return cur.area();

    Window temp;
    double a = 0;
    if (cur.x1 < overlapping[ind].x1) {
        temp = Window(cur.x1, cur.y1, overlapping[ind].x1, cur.y2, 0);
        a += getArea(temp, ind + 1);
        cur.x1 = overlapping[ind].x1;
    }
    if (cur.y1 < overlapping[ind].y1) {
        temp = Window(cur.x1, cur.y1, cur.x2, overlapping[ind].y1, 0);
        a +=getArea(temp, ind + 1);
        cur.y1 = overlapping[ind].y1;
    }
    if (cur.y2 > overlapping[ind].y2) {
        temp = Window(cur.x1, overlapping[ind].y2, cur.x2, cur.y2, 0);
        a += getArea(temp, ind + 1);
        cur.y2 = overlapping[ind].y2;
    }
    if (cur.x2 > overlapping[ind].x2) {
        temp = Window(overlapping[ind].x2, cur.y1, cur.x2, cur.y2, 0);
        a += getArea(temp, ind + 1);
        cur.x2 = overlapping[ind].x2;
    }

    return a;
}


void get_percentage(Window a)
{
    double ttl_area = a.area();
    int lv = a.level;
    overlapping.clear();


    Window cur;
    for (auto i : win) {
        cur = i.second;

        if (cur.level > lv && check_overlap(cur, a)) {
            int x1 = max(a.x1, cur.x1);
            int y1 = max(a.y1, cur.y1);
            int x2 = min(a.x2, cur.x2);
            int y2 = min(a.y2, cur.y2);

            overlapping.pb(Window(x1, y1, x2, y2, 0));
        }
    }

    double coverarea = 0;
    for (int i = 0; i < overlapping.size(); i++) {
        coverarea += getArea(overlapping[i], i + 1);
    }

    printf("%.3lf\n", (1 - (coverarea / ttl_area)) * 100);
}

int main(void)
{
    freopen("window.in", "r", stdin);
    freopen("window.out", "w", stdout);

    char curtask;
    char name;
    int a, b, c, d;
    char t;
    while (true) {
        cin >> curtask;
        if (cin.eof())
            break;

        if (curtask == 'w') {
            getchar();
            name = getchar();
            cin >> t >> a >> t >> b >> t >> c >> t >> d;
            Window temp(a, b, c, d, top++);
            win[name] = temp;
            getchar();
        }
        else if (curtask == 't') {
            getchar();
            name = getchar();
            win[name].level = top++;
            getchar();
        }
        else if (curtask == 'b') {
            getchar();
            name = getchar();
            win[name].level = --bottom;
            getchar();
        }
        else if (curtask == 'd') {
            getchar();
            name = getchar();
            win.erase(name);
            getchar();
        }
        else {
            getchar();
            name = getchar();
            get_percentage(win[name]);
            getchar();
        }
    }
}