#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    freopen("boat.in", "r", stdin);
    freopen("boat.out", "w", stdout);

    int n;
    cin >> n;

    stack<string> ships;

    for (int i = 0; i < n; i++) {
        int in, out;
        cin >> out >> in;
        for (int j = 0; j < out; j++) {
            ships.pop();
        }
        for (int j = 0; j < in; j++) {
            string ship;
            cin >> ship;
            ships.push(ship);
        }
    }

    vector<string> vec_ships(ships.size());
    int i = 0;
    while (ships.size() > 0) {
        vec_ships[i++] = ships.top();
        ships.pop();
    }

    int size = vec_ships.size();

    for (int i = 0; i < size; i++) {
        int mini = i;

        for (int j = i + 1; j < size; j++) {
            if (vec_ships[mini] > vec_ships[j])
                mini = j;
        }

        if (mini != i) {
            string temp = vec_ships[i];
            vec_ships[i] = vec_ships[mini];
            vec_ships[mini] = temp;
        }
    }

    for (int i = 0; i < size; i++) 
        cout << vec_ships[i] << '\n';
    
    return 0;
}