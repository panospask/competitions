#include <bits/stdc++.h>

using namespace std;

int main(void)
{
       list<int> my_list;

    freopen("testcases/subtask2/rafting.in17", "r", stdin);
    freopen("rafting.out", "w", stdout);

    int n;
    cin >> n;

    list<int>::iterator it;

    for (int i = 0; i < n; i++) {
        int place;
        cin >> place;
        place--;
        it = my_list.begin();
        advance(it, place);

        my_list.insert(it, i + 1);
    }

    cout << my_list.front();
    if (my_list.size() > 1) {
        it = my_list.begin();
        it++;
        for (; it != my_list.end(); it++) {
            cout << ' ' << *it;
        }
    }

    cout << endl;

    return 0;
}