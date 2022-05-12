#include <bits/stdc++.h>

using namespace std;

int diverse(int a, int b, int c)
{
    int num = 0;
    for (int i = 1; i <= 3; i++) {
        if (a == i || b == i || c == i)
            num++;
    }

    return num;
}

int main(void)
{
    freopen("miners.in", "r", stdin);
    freopen("miners.out", "w", stdout);

    int n;
    cin >> n;

    int array[n + 2];
    char c;
    for (int i = 1; i <= n; i++) {
        cin >> c;
        if (c == 'F')
            array[i] = 1;
        else if (c == 'B')
            array[i] = 2;
        else 
            array[i] = 3;
    }

    int a = 0, b = 1;
    int first1, sec1, first2, sec2;

    int table[2][4][4][4][4];
    memset(table, 0, sizeof(table));

    for (int i = n; i; i--) {
        swap(a, b);

        for (first1 = 0; first1 < 4; first1++)
            for (sec1 = 0; sec1 < 4; sec1++)
                for (first2 = 0; first2 < 4; first2++)
                    for (sec2 = 0; sec2 < 4; sec2++) {
                        int pos1 = table[b][sec1][array[i]][first2][sec2] + diverse(first1, sec1, array[i]);
                        int pos2 = table[b][first1][sec1][sec2][array[i]] + diverse(first2, sec2, array[i]);

                        table[a][first1][sec1][first2][sec2] = max(pos1, pos2);
                    }
    }

    

    cout << table[a][0][0][0][0] << endl;
    return 0;
}