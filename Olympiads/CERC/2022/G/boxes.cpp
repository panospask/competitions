#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int MAXL = 1000;

int N;
vector<pi> drawers;
vector<pi> books;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> N;
    int cur = N;

    int y = MAXL;
    int x = 1;
    while (cur >= 10) {
        for (int i = 0; i < 10; i++) {
            drawers.push_back({x + i, y - i});
        }

        books.push_back({x, y - 4});
        books.push_back({x, y - 3});
        books.push_back({x + 1, y - 2});
        books.push_back({x + 3, y - 4});
        books.push_back({x + 4, y - 5});
        books.push_back({x + 4, y - 5});
        books.push_back({x + 5, y - 9});
        books.push_back({x + 5, y - 6});
        books.push_back({x + 6, y - 9});
        books.push_back({x + 7, y - 8});


        y -= 10;
        x += 10;
        cur -= 10;
    }

    while(cur) {
        books.push_back({500, 500});
        drawers.push_back({500, 500});
        cur--;
    }

    for (auto [a, b] : books) {
        cout << a << ' ' << b << endl;
    }
    for (auto [a, b] : drawers) {
        cout << a << ' ' << b << endl;
    }
}