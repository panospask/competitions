#include <bits/stdc++.h>

using namespace std;

void print_one(int i, int print)
{
    while (i > 0) {
        cout << print << ' ';
        i--;
    }
}

void print_with_spaces(int i, int j, int k, int l, int m, int n, int o, int p, int q)
{
    print_one(i, 1);
    print_one(j, 2);
    print_one(k, 3);
    print_one(l, 4);
    print_one(m, 5);
    print_one(n, 6);
    print_one(o, 7);
    print_one(p, 8);
    print_one(q, 9);

}

void perform_new_move(int clocks[9], int new_move)
{
    stack<int> to_change;

    switch (new_move) {
        case 1: to_change.push(0); to_change.push(1); to_change.push(3); to_change.push(4); break;
        case 2: to_change.push(0); to_change.push(1); to_change.push(2); break;
        case 3: to_change.push(1); to_change.push(2); to_change.push(4); to_change.push(5); break;
        case 4: to_change.push(0); to_change.push(3); to_change.push(6); break;
        case 5: to_change.push(1); to_change.push(3); to_change.push(4); to_change.push(5); to_change.push(7); break;
        case 6: to_change.push(2); to_change.push(5); to_change.push(8); break;
        case 7: to_change.push(3); to_change.push(4); to_change.push(6); to_change.push(7); break;
        case 8: to_change.push(6); to_change.push(7); to_change.push(8); break;
        case 9: to_change.push(4); to_change.push(5); to_change.push(7); to_change.push(8); break;
    }


    while(to_change.size() > 0) {
        int i = to_change.top();

        clocks[i]++;
        clocks[i] %= 4;

        to_change.pop();
    }
}

int main(void)
{
    freopen("clocks.in", "r", stdin);
    freopen("clocks.out", "w", stdout);

    int clocks[9];
    for (int i = 0; i < 9; i++) {
        cin >> clocks[i];
    }

    for (int i = 0; i < 4; perform_new_move(clocks, 1), i++) 
        for (int j = 0; j < 4; perform_new_move(clocks, 2), j++)
            for (int k = 0; k < 4; perform_new_move(clocks, 3), k++)
                for (int l = 0; l < 4; perform_new_move(clocks, 4), l++) 
                    for (int m = 0; m < 4; perform_new_move(clocks, 5), m++)
                        for (int n = 0; n < 4; perform_new_move(clocks, 6), n++)
                            for (int o = 0; o < 4; perform_new_move(clocks, 7), o++) 
                                for (int p = 0; p < 4; perform_new_move(clocks, 8), p++)
                                    for (int q = 0; q < 4; perform_new_move(clocks, 9), q++) {
                                        if (clocks[0] + clocks[1] + clocks[2] + clocks[3] + clocks[4] + clocks[5] + clocks[6] + clocks[7] + clocks[8] == 0) {
                                            print_with_spaces(i, j, k, l, m, n, o, p, q);
                                            return 0;
                                        }
                                    }

    return 0;
}